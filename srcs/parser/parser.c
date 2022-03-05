/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/05 15:32:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_tree_node	*call_production(t_parser *parser,
										t_ast_tree_node *(*fprod)(t_parser *))
{
	size_t			idx_save;
	t_ast_tree_node *node;

	idx_save = parser->lex_idx;
	node = fprod(parser);
	parser->lex_idx = idx_save;
	return (node);
}

t_bool	match(t_parser *parser, t_token_type type, char **value)
{
	if (&(parser->lexer->tkns[parser->lex_idx]) == NULL)
		return (FALSE);
	if (parser->lexer->tkns[parser->lex_idx].type == type)
	{
		*value = parser->lexer->tkns[parser->lex_idx].val;
		parser->lex_idx++;
		return (TRUE);
	}
	parser->lex_idx++;
	return (FALSE);
}
