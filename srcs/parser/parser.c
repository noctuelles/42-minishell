/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 10:30:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* call_production() call a production rule, saving the index in the current
 * to be restore upon completion of the rule if restore is set to TRUE.  */

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		size_t save)
{
	parser->lex_idx = save;
	*root = fprod(parser);
	return (*root);
}

t_ast_tree_node	*call_term(t_parser *parser,
		t_ast_tree_node *(fterm)(t_parser *), t_ast_tree_node **root)
{
	*root = fterm(parser);
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
	if (parser->lex_idx >= parser->lexer->idx)
		return (FALSE);
	if (parser->lexer->tkns[parser->lex_idx].type == type)
	{
		if (value != NULL)
				*value = parser->lexer->tkns[parser->lex_idx].val;
		parser->lex_idx += 1;
		return (TRUE);
	}
	parser->lex_idx += 1;
	return (FALSE);
}

#include <stdio.h>

t_ast_tree_node	*parse(t_lexer *lexer)
{
	t_parser		parser;
	t_ast_tree_node	*root;

	parser.lexer = lexer;
	parser.lex_idx = 0;
	parser.errcode = NO_ERR;
	root = COMPLETE_CMD(&parser);
	if (root == NULL)
		printf("\x1b[1;31mParsing failed. Near : %s, token  %lu.\n", parser.lexer->tkns[parser.lex_idx - 1].val, parser.lex_idx - 1);
	else
		puts("\x1b[1;32mParsing sucess!");
	return (root);
}
