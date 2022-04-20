/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushnstack_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 01:58:29 by plouvel          ###   ########.fr       */
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

static inline bool	set_n_ret(t_parser *parser, t_parser_errcode errcode)
{
	set_parser_errcode(parser, errcode);
	return (false);
}

bool	check_opening_prt(t_parser *parser)
{
	if (parser->output_stack.top == NULL)
		return (set_n_ret(parser, ERR_EXPECTED_COMMAND));
	if (parser->op_stack.top == NULL)
		return (set_n_ret(parser, ERR_INVALID_PRT));
	if (cast_tkn(parser->op_stack.top)->type == T_OP_PRT)
		return (true);
	if (parser->op_stack.top->prev == NULL)
		return (set_n_ret(parser, ERR_INVALID_PRT));
	if (cast_tkn(parser->op_stack.top->prev)->type == T_OP_PRT)
		return (true);
	else
		return (set_n_ret(parser, ERR_INVALID_PRT));
}

bool	check_tkn_after_prt(t_parser *parser)
{
	t_token_type	type;

	type = curr_type(*parser);
	if (type != T_LOG_AND && type != T_LOG_OR && type != T_NULL)
		return (set_n_ret(parser, ERR_UNEXPECTED_TOKEN));
	else
		return (true);
}
