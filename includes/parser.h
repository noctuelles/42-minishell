/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:05:25 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/11 11:05:26 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast.h"

# define STR_ERR_UNEXPECTED_EOF              "unexpected end-of-file or token"
# define STR_ERR_EXPECTED_COMMAND            "expected command"
# define STR_ERR_UNEXPECTED_IO_TOKEN         "expected filename for redirection"
# define STR_ERR_UNEXPECTED_IO_HEREDOC_TOKEN "expected here-doc delimiter"
# define STR_SYNTAX_ERROR                    "syntax error"

typedef enum e_parser_errcode
{
	NO_ERR,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_UNEXPECTED_EOF,
	ERR_EXPECTED_COMMAND,
	ERR_UNEXPECTED_IO_TOKEN,
	ERR_UNEXPECTED_IO_HEREDOC_TOKEN
}	t_parser_errcode;

typedef struct	s_parser
{
	t_dlist				*tkns;
	t_parser_errcode	errcode;
}	t_parser;

/* parser_utils.c */

t_bool	match(t_parser *parser, t_token_type type, char **value);
t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		t_dlist *save);
t_ast_tree_node	*call_term(t_parser *parser,
		t_ast_tree_node *(*fterm)(t_parser *), t_ast_tree_node **root);
void	*quit_production(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode);

/* parser.c */

t_ast_tree_node	*parse(t_dlist **tkns);

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
