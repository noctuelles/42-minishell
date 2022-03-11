/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/11 17:37:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef enum e_parser_errcode
{
	ERR_MALLOC,
	ERR_SYNTAX,
	NO_ERR
}	t_parser_errcode;

typedef struct	s_parser
{
	t_lexer				*lexer;
	size_t				lex_idx;
	t_parser_errcode	errcode;
}	t_parser;

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		size_t save);
t_ast_tree_node	*call_term(t_parser *parser,
		t_ast_tree_node *(*fterm)(t_parser *), t_ast_tree_node **root);
t_bool	match(t_parser *parser, t_token_type type, char **value);
void	*quit_production(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode);
t_ast_tree_node	*parse(t_lexer *lexer);

t_ast_tree_node	*CMD_LIST(t_parser *parser);
t_ast_tree_node	*CMD_LIST1(t_parser *parser);
t_ast_tree_node	*CMD_LIST2(t_parser *parser);
t_ast_tree_node	*CMD_LIST3(t_parser *parser);

t_ast_tree_node	*CMD(t_parser *parser);
t_ast_tree_node	*CMD1(t_parser *parser);
t_ast_tree_node	*CMD2(t_parser *parser);

t_ast_tree_node	*PIPELINE(t_parser *parser);
t_ast_tree_node	*PIPELINE1(t_parser *parser);
t_ast_tree_node	*PIPELINE2(t_parser *parser);

t_ast_tree_node *SIMPLE_CMD(t_parser *parser);
t_ast_tree_node *SIMPLE_CMD1(t_parser *parser);
t_ast_tree_node *SIMPLE_CMD2(t_parser *parser);
t_ast_tree_node *SIMPLE_CMD3(t_parser *parser);
t_ast_tree_node *SIMPLE_CMD4(t_parser *parser);
t_ast_tree_node *SIMPLE_CMD5(t_parser *parser);

t_ast_tree_node	*CMD_PREFIX(t_parser *parser);
t_ast_tree_node	*CMD_PREFIX1(t_parser *parser);
t_ast_tree_node	*CMD_PREFIX2(t_parser *parser);

t_ast_tree_node	*CMD_SUFFIX(t_parser *parser);
t_ast_tree_node	*CMD_SUFFIX1(t_parser *parser);
t_ast_tree_node	*CMD_SUFFIX2(t_parser *parser);
t_ast_tree_node	*CMD_SUFFIX3(t_parser *parser);
t_ast_tree_node	*CMD_SUFFIX4(t_parser *parser);

t_ast_tree_node	*IO_REDIRECT(t_parser *parser);
t_ast_tree_node	*IO_REDIRECT1(t_parser *parser);
t_ast_tree_node	*IO_REDIRECT2(t_parser *parser);
t_ast_tree_node	*IO_REDIRECT3(t_parser *parser);
t_ast_tree_node	*IO_REDIRECT4(t_parser *parser);

#endif
