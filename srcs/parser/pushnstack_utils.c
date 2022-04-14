/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushnstack_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:54:22 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 16:49:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_type	curr_type(t_parser parser)
{
	return (parser.curr_tkn->type);
}

bool	is_top_an_operator(t_parser parser)
{
	t_token	*top_tkn;

	top_tkn = parser.op_stack.top->content;
	if (top_tkn->type == T_LOG_AND || top_tkn->type == T_LOG_OR)
		return (true);
	else
		return (false);
}

t_token	*cast_tkn(t_dlist *elem)
{
	return ((t_token *) elem->content);
}

void	consume_token(t_parser *parser)
{
	parser->tkns = parser->tkns->next;
	parser->curr_tkn = (t_token *) parser->tkns->content;
}

void	rollback_token(t_parser *parser)
{
	parser->tkns = parser->tkns->prev;
	parser->curr_tkn = (t_token *) parser->tkns->content;
}

bool	is_a_redirection(t_token_type type)
{
	if (type == T_GRT || type == T_LESS ||
		type == T_DGRT || type == T_DLESS)
		return (true);
	else
		return (false);
}
