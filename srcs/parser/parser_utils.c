/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:57:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 19:36:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode)
{
	parser->errcode = errcode;
	return (NULL);
}

t_token_type	curr_type(t_parser parser)
{
	return (parser.curr_tkn->type);
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

t_token	*cast_tkn(t_dlist *elem)
{
	return ((t_token *) elem->content);
}
