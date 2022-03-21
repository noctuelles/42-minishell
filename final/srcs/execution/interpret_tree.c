/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/21 21:32:41 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>
#include "minishell.h"

void	parse_tree(t_ast_tree_node *node, t_command *command, t_args **args)
{
	t_args	*elem;

	if (node->type == NODE_COMMAND_SUFFIX && node->value != NULL && !command->error)
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
	if (node->type == NODE_IO_REDIRECT_STDIN && !command->error)
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
	if (node->type == NODE_IO_REDIRECT_FILE && !command->error)
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
	if (node->type == NODE_IO_REDIRECT_FILE_APPEND && !command->error)
	{
		if (command->io_out_redirect > 0)
			close(command->io_out_redirect);
		command->io_out_redirect = open(node->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (command->io_out_redirect < 0)
		{
			command->io_out_redirect = -2;
			command->out_errno = errno;
			command->error = true;
		}
		command->out_name = node->value;
	}
	if (node->type == NODE_IO_REDIRECT_HERE_DOC && !command->error)
	{
		int pipefd[2];
		if(pipe(pipefd) < 0)
		{
			printf("Pipe error\n");
			exit(1);
		}
		while(1)
		{
			char *line = readline("> ");
			if(line != NULL)
			{
				if(strcmp(line, node->value) != 0)
				{
					write(pipefd[1], line, strlen(line));
					write(pipefd[1], "\n", 1);
				}
				else
					break;
			}
		}
		close(pipefd[1]);
			command->io_in_redirect = pipefd[0];
	}
	if (node->left != NULL && !command->error)
		parse_tree(node->left, command, args);
	if (node->right != NULL && !command->error)
		parse_tree(node->right, command, args);
}

t_command	*parse_command(t_ast_tree_node *node, bool piped)
{
	t_command	*command;
	t_args		*args;
	int			length;
	t_args		*elem;
	int			i;

	command = calloc(sizeof(t_command), 1);
	command->is_piped = piped;
	command->name = node->value;
	command->io_in_redirect = -1;
	command->io_out_redirect = -1;
	command->error = false;
	args = NULL;
	if (node->left != NULL)
		parse_tree(node->left, command, &args);
	if (node->right != NULL)
		parse_tree(node->right, command, &args);
	length = 0;
	elem = args;
	while (elem)
	{
		length++;
		elem = elem->next;
	}
	command->args = calloc(sizeof(char *), length + 1);
	i = 0;
	while (args)
	{
		command->args[i] = args->value;
		elem = args;
		args = args->next;
		free(elem);
		i++;
	}
	command->args[i] = NULL;
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
	(void)vars;
	t_command	*first;

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