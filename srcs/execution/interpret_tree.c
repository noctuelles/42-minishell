/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 14:03:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>

extern int	g_sigint;

void	append_arg(t_ast_tree_node *node, t_args **el, t_args **args,
	t_command *command)
{
	t_args	*elem;

	elem = *el;
	if (node->type == NODE_COMMAND_SUFFIX && node->value != NULL
		&& !command->error)
	{
		if (*args == NULL)
		{
			*args = calloc(sizeof(t_args), 1);
			(*args)->next = NULL;
			(*args)->value = node->value;
		}
		else
		{
			elem = *args;
			while (elem->next != NULL)
				elem = elem->next;
			elem->next = calloc(sizeof(t_args), 1);
			elem->next->next = NULL;
			elem->next->value = node->value;
		}
	}
}

void	set_io_stdin(t_ast_tree_node *node, t_command *command)
{
	if (node->type == NODE_IO_REDIRECT_STDIN && !command->error
		&& node->value != NULL)
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

void	set_io_stdout(t_ast_tree_node *node, t_command *command)
{
	if (node->type == NODE_IO_REDIRECT_FILE && !command->error
		&& node->value != NULL)
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

void	set_io_stdout_append(t_ast_tree_node *node, t_command *command)
{
	if (node->type == NODE_IO_REDIRECT_FILE_APPEND && !command->error
		&& node->value != NULL)
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

int	treat_line(char *line, t_ast_tree_node *node, int pipefd[2])
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

void	here_doc_read(t_ast_tree_node *node, int pipefd[2], t_command *command)
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

void	here_doc_logic(t_ast_tree_node *node, t_command *command)
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

void	parse_tree(t_ast_tree_node *node, t_command *command, t_args **args)
{
	t_args	*elem;

	append_arg(node, &elem, args, command);
	set_io_stdin(node, command);
	set_io_stdout(node, command);
	set_io_stdout_append(node, command);
	if (node->type == NODE_IO_REDIRECT_HERE_DOC && node->value != NULL)
		here_doc_logic(node, command);
	if (node->left != NULL && !command->error)
		parse_tree(node->left, command, args);
	if (node->right != NULL && !command->error)
		parse_tree(node->right, command, args);
}

t_command	*prepare_command(bool piped, t_ast_tree_node *node, t_args **args)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->is_piped = piped;
	command->name = strdup(node->value);
	command->original_name = NULL;
	command->io_in_redirect = -1;
	command->io_out_redirect = -1;
	command->error = false;
	*args = NULL;
	if (node->left != NULL)
		parse_tree(node->left, command, args);
	if (node->right != NULL)
		parse_tree(node->right, command, args);
	return (command);
}

void	set_args(t_command *command, t_args *args)
{
	int		i;
	t_args	*elem;

	i = 0;
	while (args)
	{
		command->args[i] = strdup(args->value);
		elem = args;
		args = args->next;
		free(elem);
		i++;
	}
	command->args[i] = NULL;
}

t_command	*parse_command(t_ast_tree_node *node, bool piped)
{
	t_command	*command;
	t_args		*args;
	int			length;
	t_args		*elem;

	command = prepare_command(piped, node, &args);
	length = 0;
	elem = args;
	while (elem)
	{
		length++;
		elem = elem->next;
	}
	command->args = calloc(sizeof(char *), length + 1);
	set_args(command, args);
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
