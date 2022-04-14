/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 20:15:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "libft.h"
#include <stdlib.h>

bool	is_a_redirection(t_token_type type)
{
	if (type == T_GRT || type == T_LESS
		|| type == T_DGRT || type == T_DLESS)
		return (true);
	else
		return (false);
}

static void	*clean(t_parser *parser, t_dlist **args, t_parser_errcode errcode)
{
	if (errcode != ERR_KEEP)
		set_parser_errcode(parser, errcode);
	ft_dlstclear(args, free_arg);
	return (NULL);
}

static t_arg	*handle_redirection_tkn(t_parser *parser, t_dlist **args,
		t_token_type type)
{
	t_arg	*arg;

	consume_token(parser);
	if (curr_type(*parser) == T_WORD)
	{
		arg = add_arg_to_list(parser, args, type);
		if (!arg)
			return (set_parser_errcode(parser, ERR_MALLOC));
	}
	else
	{
		if (type == T_DLESS)
			parser->errcode = ERR_UNEXPECTED_IO_HEREDOC_TOKEN;
		else
			parser->errcode = ERR_UNEXPECTED_IO_TOKEN;
		return (NULL);
	}
	return (arg);
}

static t_dlist	*parse_simple_cmd(t_parser *parser)
{
	t_dlist			*args;
	t_token_type	type;

	args = NULL;
	while (true)
	{
		type = curr_type(*parser);
		if (is_a_redirection(type))
		{
			if (!handle_redirection_tkn(parser, &args, type))
				return (clean(parser, &args, ERR_KEEP));
		}
		else if (type == T_WORD)
		{
			if (!add_arg_to_list(parser, &args, type))
				return (clean(parser, &args, ERR_MALLOC));
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

	if (curr_type(*parser) == T_NULL)
		return (set_parser_errcode(parser, ERR_EXPECTED_COMMAND));
	args = parse_simple_cmd(parser);
	if (!args)
		return (NULL);
	node = ast_tree_create_node(args, NODE_COMMAND);
	if (!node)
		return (clean(parser, &args, ERR_MALLOC));
	return (node);
}
