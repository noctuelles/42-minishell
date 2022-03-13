/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:47:44 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/13 22:36:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_command
{
	char *name;
	char **args;
	char *io_in_redirect;
	char *io_out_redirect;
	bool is_piped;
}	t_command;

typedef struct s_args
{
	char *value;
	struct s_args *next;
}	t_args;

void	parse_tree(t_ast_tree_node *node, t_command *command, t_args **args)
{
	if(node->type == NODE_COMMAND_SUBSHELL)
	{
		if(*args == NULL)
		{
			*args = calloc(sizeof(t_args), 1);
			(*args)->next = NULL;
			(*args)->value = node->value;
		}
		else
		{
			t_args *elem = *args;
			while(elem->next != NULL)
				elem = elem->next;
			elem->next = calloc(sizeof(t_args), 1);
			elem->next->next = NULL;
			elem->next->value = node->value;
		}
	}
	if(node->type == NODE_IO_REDIRECT_STDIN)
		command->io_in_redirect = node->value;
	if(node->type == NODE_IO_REDIRECT_FILE)
		command->io_out_redirect = node->value;
	if(node->left != NULL)
		parse_tree(node->left, command, args);
	if(node->right != NULL)
		parse_tree(node->right, command, args);
}

t_command	*parse_command(t_ast_tree_node *node)
{
	t_command *command;
	t_args	*args;

	command = calloc(sizeof(t_command), 1);
	if(node->type == NODE_COMMAND)
		command->is_piped = true;
	if(node->type == NODE_COMMAND_IMMEDIATE)
		command->is_piped = false;
	command->name = node->value;
	args = NULL;
	if(node->left != NULL)
		parse_tree(node->left, command, &args);
	if(node->right != NULL)
		parse_tree(node->right, command, &args);
	int length = 0;
	t_args *elem = args;
	while(elem)
	{
		length++;
		elem = elem->next;
	}
	command->args = calloc(sizeof(char*), length + 1);
	int i = 0;
	while(args)
	{
		command->args[i] = args->value;
		t_args *tmp = args;
		args = args->next;
		free(tmp);
		i++;
	}
	command->args[i] = NULL;
}