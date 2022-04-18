/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushnstack_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 18:43:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_top_an_operator(t_parser parser)
{
	t_token	*top_tkn;

	top_tkn = parser.op_stack.top->content;
	if (top_tkn->type == T_LOG_AND || top_tkn->type == T_LOG_OR)
		return (true);
	else
		return (false);
}

bool	check_opening_prt(t_parser *parser)
{
	if (parser->op_stack.top == NULL)
	{
		set_parser_errcode(parser, ERR_INVALID_PRT);
		return (false);
	}
	if (cast_tkn(parser->op_stack.top)->type == T_OP_PRT)
		return (true);
	if (parser->op_stack.top->prev == NULL)
	{
		set_parser_errcode(parser, ERR_INVALID_PRT);
		return (false);
	}
	if (cast_tkn(parser->op_stack.top->prev)->type == T_OP_PRT)
		return (true);
	else
	{
		set_parser_errcode(parser, ERR_INVALID_PRT);
		return (false);
	}
}

bool	check_tkn_after_prt(t_parser *parser)
{
	t_token_type	type;

	type = curr_type(*parser);
	if (type != T_LOG_AND && type != T_LOG_OR && type != T_NULL)
	{
		set_parser_errcode(parser, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	else
		return (true);
}
