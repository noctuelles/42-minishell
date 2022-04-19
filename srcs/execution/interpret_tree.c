/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 12:04:33 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include <readline/readline.h>

extern int	g_sigint;

char	*create_path(char *path, char *command_name)
{
	char	*exec_path;

	exec_path = malloc(sizeof(char)
			* (ft_strlen(path) + ft_strlen(command_name) + 2));
	exec_path[0] = '\0';
	ft_strcat(exec_path, path);
	ft_strcat(exec_path, "/");
	ft_strcat(exec_path, command_name);
	return (exec_path);
}

void	not_found(char **exec_path)
{
	free(*exec_path);
	*exec_path = NULL;
}

char	*get_path_from_env(char *command_name, t_minishell *minishell)
{
	char	*path;
	char	*cpy;
	int		found;
	char	*exec_path;

	found = 0;
	exec_path = NULL;
	if (get_var(minishell->vars, "PATH") != NULL)
	{
		cpy = ft_strdup(get_var(minishell->vars, "PATH")->value);
		path = cpy;
		while (ft_strtrunc(&path, ':'))
		{
			if (!found)
			{
				exec_path = create_path(path, command_name);
				if (access(exec_path, F_OK) == 0)
					found = 1;
				else
					not_found(&exec_path);
			}
		}
		free(cpy);
	}
	return (exec_path);
}

char	*get_path_from_name(char *name, t_minishell *minishell,
	t_command *command)
{
	char	*path;

	if (ft_strchr(name, '/') == NULL)
	{
		if (!is_builtin(name))
		{
			command->is_name_malloc = 1;
			path = get_path_from_env(name, minishell);
			if (!path)
				ft_dprintf(2, COMMAND_NOT_FOUND, name);
			return (path);
		}
		else
			return (name);
	}
	else
	{
		if (access(name, F_OK) == 0)
			return (name);
		ft_dprintf(2, ERROR_ERRNO, name, strerror(errno));
		return (NULL);
	}
}

void	count_arg(t_arg *node, int *arg_count)
{
	if (node->type == ARG_WORD)
	{
		(*arg_count)++;
	}
}

void	add_io(t_arg *node, t_command *command)
{
	if (node->type == ARG_REDIRECT_STDIN)
	{
		ft_dlstadd_back(&(command->io_in), ft_dlstnew(node));
		if (command->here_doc > 0)
		{
			close(command->here_doc);
			command->here_doc = -1;
		}
	}
	if (node->type == ARG_REDIRECT_FILE || node->type
		== ARG_REDIRECT_FILE_APPEND)
	{
		ft_dlstadd_back(&(command->io_out), ft_dlstnew(node));
	}
}

int	treat_line(char *line, t_arg *node, int pipefd[2], t_command *command)
{
	if (ft_strnstr(line, node->value, ft_strlen(line)) == NULL)
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		return (0);
	}
	else
	{
		command->here_doc = pipefd[0];
		free(line);
		return (1);
	}
}

void	here_doc_read(t_arg *node, int pipefd[2], t_command *command)
{
	char	*line;
	int		count;

	count = 1;
	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (treat_line(line, node, pipefd, command))
				break ;
			count++;
		}
		else
		{
			if (g_sigint)
			{
				ft_dprintf(1, "\n");
				break ;
			}
			ft_dprintf(1, HERE_DOC_EOF, count, node->value);
			break ;
		}
	}
}

void	here_doc_logic(t_arg *node, t_command *command)
{
	int		pipefd[2];
	
	if (pipe(pipefd) < 0)
	{
		ft_dprintf(1, PIPE_ERROR);
		exit(1);
	}
	set_signals_as_here_doc();
	here_doc_read(node, pipefd, command);
	set_signals_as_prompt();
	close(pipefd[1]);
	command->here_doc = pipefd[0];
}

void	parse_list(t_dlist *node, t_command *command, int *arg_count)
{
	count_arg(node->content, arg_count);
	add_io(node->content, command);
	if (((t_arg *)node->content)->type == ARG_REDIRECT_HERE_DOC)
		here_doc_logic(node->content, command);
	if (node->next != NULL && !g_sigint)
		parse_list(node->next, command, arg_count);
}

t_command	*init_cmd(void)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	command->io_in = NULL;
	command->io_out = NULL;
	command->here_doc = -1;
	command->empty_command = 0;
	command->is_name_malloc = 0;
	return (command);
}

t_command	*prepare_command(bool piped, t_ast_tree_node *node,
	int *arg_count, t_minishell *minishell)
{
	t_command	*command;

	command = init_cmd();
	if (node->args != NULL)
	{
		command->is_piped = piped;
		command->name = get_path_from_name(
				((t_arg *)node->args->content)->value, minishell, command);
		if (!command->name)
			return (command);
		*arg_count = 1;
		if (node->args->next != NULL)
			parse_list(node->args->next, command, arg_count);
	}
	else
	{
		command->empty_command = 1;
		command->name = NULL;
	}
	return (command);
}

t_command	*parse_command(t_ast_tree_node *node, bool piped,
	t_minishell *minishell)
{
	t_command	*command;
	int			args_count;
	t_dlist		*elem;
	int			i;

	command = prepare_command(piped, node, &args_count, minishell);
	if (command->name != NULL && !g_sigint)
	{
		command->args = ft_calloc(sizeof(char *), args_count + 1);
		elem = node->args;
		i = 0;
		while (elem)
		{
			if (((t_arg *)elem->content)->type == ARG_WORD)
			{
				command->args[i] = ((t_arg *)elem->content)->value;
				i++;
			}
			elem = elem->next;
		}
	}
	command->next = NULL;
	return (command);
}

void	add_command(t_command *cmd, t_command **lst)
{
	t_command	*elem;

	if (*lst == NULL)
		*lst = cmd;
	else
	{
		elem = *lst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = cmd;
	}
}

t_command	*parse_commands(t_ast_tree_node *root, t_minishell *minishell)
{
	t_command	*first;

	(void)minishell->vars;
	first = NULL;
	apply_expansion_on_node(root, minishell);
	if (root->type == NODE_COMMAND)
	{
		first = parse_command(root, false, minishell);
	}
	else
	{
		while (root->type == NODE_PIPE && !g_sigint)
		{
			add_command(parse_command(root->left, true, minishell), &first);
			root = root->right;
		}
		if (!g_sigint)
			add_command(parse_command(root, false, minishell), &first);
	}
	return (first);
}

void	parse_and_or(t_ast_tree_node *node, t_minishell *minishell)
{
	if (node->left == NULL || node->right == NULL)
		return ;
	if (node->left->type == NODE_LOGICAL_AND
		|| node->left->type == NODE_LOGICAL_OR)
		parse_and_or(node->left, minishell);
	else if (node->left->type == NODE_COMMAND || node->left->type == NODE_PIPE)
		minishell->last_ret = execute_pipeline(node->left, minishell) % 256;
	if ((minishell->last_ret == 0 && node->type == NODE_LOGICAL_AND)
		|| (minishell->last_ret != 0 && node->type == NODE_LOGICAL_OR))
	{
		if (node->right->type == NODE_LOGICAL_AND
			|| node->right->type == NODE_LOGICAL_OR)
			parse_and_or(node->right, minishell);
		else if (node->right->type == NODE_COMMAND
			|| node->right->type == NODE_PIPE)
			minishell->last_ret
				= execute_pipeline(node->right, minishell) % 256;
	}
}
