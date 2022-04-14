/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 16:49:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include <stdlib.h>

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

t_dlist *simple_command(t_parser *parser)
{
	t_dlist			*args;
	t_token_type	type;
	t_arg			*arg;
	t_dlist			*elem;

	args = NULL;
	if (curr_type(*parser) == T_NULL)
	{
		rollback_token(parser);
		return (set_parser_errcode(parser, ERR_EXPECTED_COMMAND));
	}
	while (true)
	{
		type = curr_type(*parser);
		if (is_a_redirection(type))
		{
			consume_token(parser);
			if (curr_type(*parser) == T_WORD)
			{
				arg = new_arg(parser->curr_tkn->val, type);
				if (!arg)
					return (set_parser_errcode(parser, ERR_MALLOC));
				elem = ft_dlstnew(arg);
				if (!elem)
					return (set_parser_errcode(parser, ERR_MALLOC));
				ft_dlstadd_back(&args, elem);
				consume_token(parser);
			}
			else
			{
				if (type == T_DLESS)
					parser->errcode = ERR_UNEXPECTED_IO_HEREDOC_TOKEN;
				else
					parser->errcode = ERR_UNEXPECTED_IO_TOKEN;
				return (NULL);
			}
		}
		else if (type == T_WORD)
		{
			arg = new_arg(parser->curr_tkn->val, type);
			if (!arg)
				return (set_parser_errcode(parser, ERR_MALLOC));
			elem = ft_dlstnew(arg);
			if (!elem)
				return (set_parser_errcode(parser, ERR_MALLOC));
			ft_dlstadd_back(&args, elem);
			consume_token(parser);
		}
		else
			break ;
	}
	return (args);
}

t_ast_tree_node	*simple_cmd(t_parser *parser)
{
	t_dlist			*args;
	t_ast_tree_node	*node;

	args = simple_command(parser);
	if (args == NULL)
		return (NULL);
	node = ast_tree_create_node(args, NODE_COMMAND);
	if (!node)
		return (NULL);
	return (node);
}
