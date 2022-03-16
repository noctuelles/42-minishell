/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/12 15:32:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef enum e_parser_errcode
{
	NO_ERR,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_UNEXCEPTED_EOF,
	ERR_EXCEPTED_COMMAND,
	ERR_UNEXCEPTED_IO_TOKEN,
	ERR_UNEXCEPTED_IO_HEREDOC_TOKEN
}	t_parser_errcode;

typedef struct	s_parser
{
	t_lexer				*lexer;
	size_t				lex_idx;
	t_parser_errcode	errcode;
}	t_parser;

/* parser_utils.c */

t_bool	match(t_parser *parser, t_token_type type, char **value);
t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		size_t save);
t_ast_tree_node	*call_term(t_parser *parser,
		t_ast_tree_node *(*fterm)(t_parser *), t_ast_tree_node **root);
void	*quit_production(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode);
char	*get_parse_error(t_parser_errcode errcode);

/* parser.c */

t_ast_tree_node	*parse(char *str);

/* Prototype for each production rules : */

t_ast_tree_node	*complete_cmd(t_parser *parser);

t_ast_tree_node	*pipeline(t_parser *parser);
t_ast_tree_node	*pipeline1(t_parser *parser);
t_ast_tree_node	*pipeline2(t_parser *parser);

t_ast_tree_node	*and_or(t_parser *parser);
t_ast_tree_node	*and_or1(t_parser *parser);
t_ast_tree_node	*and_or2(t_parser *parser);
t_ast_tree_node	*and_or3(t_parser *parser);

t_ast_tree_node	*cmd(t_parser *parser);
t_ast_tree_node	*cmd1(t_parser *parser);
t_ast_tree_node	*cmd2(t_parser *parser);

t_ast_tree_node *simple_cmd(t_parser *parser);
t_ast_tree_node *simple_cmd1(t_parser *parser);
t_ast_tree_node *simple_cmd2(t_parser *parser);
t_ast_tree_node *simple_cmd3(t_parser *parser);
t_ast_tree_node *simple_cmd4(t_parser *parser);
t_ast_tree_node *simple_cmd5(t_parser *parser);

t_ast_tree_node	*io_list(t_parser *parser);
t_ast_tree_node	*io_list1(t_parser *parser);
t_ast_tree_node	*io_list2(t_parser *parser);

t_ast_tree_node	*cmd_suffix(t_parser *parser);
t_ast_tree_node	*cmd_suffix1(t_parser *parser);
t_ast_tree_node	*cmd_suffix2(t_parser *parser);
t_ast_tree_node	*cmd_suffix3(t_parser *parser);
t_ast_tree_node	*cmd_suffix4(t_parser *parser);

t_ast_tree_node	*io_redirect(t_parser *parser);
t_ast_tree_node	*io_redirect1(t_parser *parser);
t_ast_tree_node	*io_redirect2(t_parser *parser);
t_ast_tree_node	*io_redirect3(t_parser *parser);
t_ast_tree_node	*io_redirect4(t_parser *parser);

#endif
