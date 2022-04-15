/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/15 16:19:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>

extern int	g_sigint;

void	count_arg(t_arg *node, int *arg_count)
{
	if (node->type == ARG_WORD)
		(*arg_count)++;
}

void	set_io_stdin(t_arg *node, t_command *command)
{
	if (node->type == ARG_REDIRECT_STDIN && !command->error)
	{
		if (command->io_in_redirect > 0)
			close(command->io_in_redirect);
		command->io_in_redirect = open(node->value, O_RDONLY);
		if (command->io_in_redirect < 0)
		{
			command->io_in_redirect = -2;
			command->in_errno = errno;
			command->error = true;
		}
		command->in_name = node->value;
	}
}

void	set_io_stdout(t_arg *node, t_command *command)
{
	if (node->type == ARG_REDIRECT_FILE && !command->error)
	{
		if (command->io_out_redirect > 0)
			close(command->io_out_redirect);
		command->io_out_redirect = open(node->value, O_WRONLY | O_CREAT, 0644);
		if (command->io_out_redirect < 0)
		{
			command->io_out_redirect = -2;
			command->out_errno = errno;
			command->error = true;
		}
		command->out_name = node->value;
	}
}

void	set_io_stdout_append(t_arg *node, t_command *command)
{
	if (node->type == ARG_REDIRECT_FILE_APPEND && !command->error)
	{
		if (command->io_out_redirect > 0)
			close(command->io_out_redirect);
		command->io_out_redirect = open(node->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (command->io_out_redirect < 0)
		{
			command->io_out_redirect = -2;
			command->out_errno = errno;
			command->error = true;
		}
		command->out_name = node->value;
	}
}

int	treat_line(char *line, t_arg *node, int pipefd[2])
{
	if (strcmp(line, node->value) != 0)
	{
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		return (0);
	}
	else
		return (1);
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
			if (treat_line(line, node, pipefd))
				break ;
			count++;
		}
		else
		{
			if (g_sigint)
			{
				command->error = true;
				printf("\n");
				break ;
			}
			printf(HERE_DOC_EOF, count, node->value);
			break ;
		}
	}
}

void	here_doc_logic(t_arg *node, t_command *command)
{
	int		pipefd[2];

	if (command->io_in_redirect > 0)
		close(command->io_in_redirect);
	if (pipe(pipefd) < 0)
	{
		printf(PIPE_ERROR);
		exit(1);
	}
	set_signals_as_here_doc();
	here_doc_read(node, pipefd, command);
	set_signals_as_prompt();
	close(pipefd[1]);
	command->io_in_redirect = pipefd[0];
}

void	parse_list(t_dlist *node, t_command *command, int *arg_count)
{
	count_arg(node->content, arg_count);
	set_io_stdin(node->content, command);
	set_io_stdout(node->content, command);
	set_io_stdout_append(node->content, command);
	if (((t_arg *)node->content)->type == ARG_REDIRECT_HERE_DOC)
		here_doc_logic(node->content, command);
	if (node->next != NULL)
		parse_list(node->next, command, arg_count);
}

t_command	*prepare_command(bool piped, t_ast_tree_node *node, int *arg_count)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->is_piped = piped;
	command->name = strdup(((t_arg *)node->args->content)->value);
	command->original_name = NULL;
	command->io_in_redirect = -1;
	command->io_out_redirect = -1;
	command->error = false;
	*arg_count = 0;
	if (node->args->next != NULL)
		parse_list(node->args->next, command, arg_count);
	return (command);
}

t_command	*parse_command(t_ast_tree_node *node, bool piped)
{
	t_command	*command;
	int			args_count;
	t_dlist		*elem;
	int			i;

	command = prepare_command(piped, node, &args_count);
	command->args = calloc(sizeof(char *), args_count + 1);
	elem = node->args;
	i = 0;
	while(elem)
	{
		if(((t_arg *)elem->content)->type == ARG_WORD)
		{
			command->args[i] = strdup(((t_arg *)elem->content)->value);
			i++;
		}
		elem = elem->next;
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

t_command	*parse_commands(t_ast_tree_node *root, t_dlist *vars)
{
	t_command	*first;

	(void)vars;
	first = NULL;
	// Expansion on the current node
	if (root->type == NODE_COMMAND)
	{
		first = parse_command(root, false);
	}
	else
	{
		while (root->type == NODE_PIPE)
		{
			add_command(parse_command(root->left, true), &first);
			root = root->right;
		}
		add_command(parse_command(root, false), &first);
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
		minishell->last_ret = execute_pipeline(node->left, *minishell);
	node->left = NULL;
	if ((minishell->last_ret == 0 && node->type == NODE_LOGICAL_AND)
		|| (minishell->last_ret != 0 && node->type == NODE_LOGICAL_OR))
	{
		if (node->right->type == NODE_LOGICAL_AND
			|| node->right->type == NODE_LOGICAL_OR)
			parse_and_or(node->right, minishell);
		else if (node->right->type == NODE_COMMAND
			|| node->right->type == NODE_PIPE)
			minishell->last_ret = execute_pipeline(node->right, *minishell);
		node->right = NULL;
	}
	ast_tree_delete_node(node);
}
