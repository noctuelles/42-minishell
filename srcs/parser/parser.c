/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/07 17:22:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* call_production() call a production rule, saving the index in the current
 * to be restore upon completion of the rule if restore is set to TRUE.  */

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		t_bool restore)
{
	size_t			idx_save;

	if (restore == TRUE)
	{
		idx_save = parser->lex_idx;
		*root = fprod(parser);
		parser->lex_idx = idx_save;
	}
	else
		*root = fprod(parser);
	return (*root);
}

void	*quit_production(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode)
{
	if (left != NULL)
		ast_tree_delete_node(left);
	if (right != NULL)
		ast_tree_delete_node(right);
	if (parser->errcode != ERR_MALLOC)
		parser->errcode = errcode;
	return (NULL);
}

t_bool	match(t_parser *parser, t_token_type type, char **value)
{
	if (parser->lexer->tkns[parser->lex_idx].type == type)
	{
		if (*value != NULL)
			*value = parser->lexer->tkns[parser->lex_idx].val;
		parser->lex_idx++;
		return (TRUE);
	}
	parser->lex_idx++;
	return (FALSE);
}
