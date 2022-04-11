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

typedef struct	s_parse_stack
{
	t_dlist	*top;
	t_dlist	*cnt;
}	t_parse_stack;

typedef struct	s_parser
{
	t_dlist				*tkns;
	t_token				*last_used_tkn;
	t_parser_errcode	errcode;
	t_parse_stack		*output_stack;
	t_parse_stack		*op_stack;
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

t_ast_tree_node	*pipeline(t_parser *parser);
t_ast_tree_node	*pipeline1(t_parser *parser);
t_ast_tree_node	*pipeline2(t_parser *parser);
t_ast_tree_node	*pipeline3(t_parser *parser);
t_ast_tree_node	*pipeline4(t_parser *parser);
t_ast_tree_node	*pipeline5(t_parser *parser);

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

/* stack.c */

t_dlist			*push_stack(t_parse_stack *stack, void *content);
void			pop_stack(t_parse_stack *stack, void (*del)(void *));
t_token_type	*new_token_type(t_token_type type);

#endif
