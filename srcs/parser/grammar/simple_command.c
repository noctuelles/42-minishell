/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/13 18:22:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include <stdlib.h>

t_ast_tree_node	*simple_cmd(t_parser *parser)
{
	t_ast_tree_node	*node;
	t_dlist			*save;

	save = parser->tkns;
	if (call_production(parser, &simple_cmd1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd4, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd5, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_arg	*new_arg(char *value, t_token_type token_type)
{
	t_arg		*arg;
	char		*arg_value;
	t_arg_type	arg_type;

	if (token_type == T_GRT)
		arg_type = ARG_REDIRECT_FILE;
	else if (token_type == T_LESS)
		arg_type = ARG_REDIRECT_STDIN;
	else if (token_type == T_DGRT)
		arg_type = ARG_REDIRECT_FILE_APPEND;
	else if (token_type == T_DLESS)
		arg_type = ARG_REDIRECT_HERE_DOC;
	else
		arg_type = ARG_WORD;
	arg = (t_arg *) malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg_value = ft_strdup(value);
	if (!arg_value)
	{
		free(arg);
		return (NULL);
	}
	arg->type = arg_type;
	arg->value = arg_value;
	return (arg);
}

t_ast_tree_node *simple_command(t_parser *parser)
{
	t_dlist			*args;
	t_token_type	type;
	t_arg			*arg;
	t_dlist			*elem;

	args = NULL;
	while (true)
	{
		type = curr_type(*parser);
		if (is_a_redirection(type))
		{
			consume_token(parser);
			if (curr_type(*parser) == T_WORD)
			{
				arg = new_arg(parser->curr_tkn->val, type);
				if (arg)
					return (NULL);
				elem = ft_dlstnew(arg);
				if (!elem)
					return (NULL);
				ft_dlstadd_back(&args, elem);
			}
			else
				return (NULL);
		}
		if (type == T_WORD)
		{
			arg = new_arg(parser->curr_tkn->val, type);
			if (arg)
				return (NULL);
			elem = ft_dlstnew(arg);
			if (!elem)
				return (NULL);
			ft_dlstadd_back(&args, elem);
			consume_token(parser);
		}
		else
			break ;
	}
}
