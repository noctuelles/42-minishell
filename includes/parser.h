/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/05 15:33:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

typedef enum	s_node_type
{
	NUL = 0
}	t_node_type;

typedef struct	s_ast_tree_node
{
	t_node_type				type;
	char					*value;
	struct s_ast_tree_node	*left;
	struct s_ast_tree_node	*right;
}	t_ast_tree_node;

typedef struct	s_parser
{
	t_lexer	*lexer;
	size_t	lex_idx;
}	t_parser;

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *));

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
