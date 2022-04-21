/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:05:25 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:20:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast.h"
# include "env.h"

/******************************************************************************
 *                                  Macros                                    *
 *****************************************************************************/

# define STR_ERR_UNEXPECTED_TOKEN            "unexpected token"
# define STR_ERR_EXPECTED_COMMAND            "expected command"
# define STR_ERR_UNEXPECTED_IO_TOKEN         "expected filename for redirection"
# define STR_ERR_UNEXPECTED_IO_HEREDOC_TOKEN "expected here-doc delimiter"
# define STR_SYNTAX_ERROR                    "syntax error"

/******************************************************************************
 *                              Typedef & Enum                                *
 *****************************************************************************/

typedef enum e_parser_errcode
{
	NO_ERR,
	ERR_KEEP,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_EXPECTED_COMMAND,
	ERR_UNEXPECTED_TOKEN,
	ERR_UNEXPECTED_IO_TOKEN,
	ERR_UNEXPECTED_IO_HEREDOC_TOKEN,
	ERR_INVALID_PRT
}	t_parser_errcode;

typedef enum e_arg_type
{
	ARG_WORD,
	ARG_REDIRECT_STDIN,
	ARG_REDIRECT_FILE,
	ARG_REDIRECT_FILE_APPEND,
	ARG_REDIRECT_HERE_DOC
}	t_arg_type;

typedef struct s_arg
{
	char		*value;
	size_t		len;
	t_arg_type	type;
	t_list		*quote_lst;
	t_list		*rem_quote_lst;
	t_list		*wldc_lst;
	char		quote;
}	t_arg;

typedef struct s_parse_stack
{
	t_dlist	*top;
	t_dlist	*cnt;
}	t_parse_stack;

typedef struct s_parser
{
	t_dlist				*tkns;
	t_token				*last_used_tkn;
	t_token				*curr_tkn;
	t_parser_errcode	errcode;
	t_parse_stack		output_stack;
	t_parse_stack		op_stack;
}	t_parser;

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

/* simple_command.c */

bool			is_a_redirection(t_token_type type);
t_ast_tree_node	*simple_cmd(t_parser *parser);

/* pipeline.c */

t_ast_tree_node	*pipeline(t_parser *parser);

/* parser_utils.c */

void			*set_parser_errcode(t_parser *parser, t_parser_errcode errcode);
t_token_type	curr_type(t_parser parser);
t_token			*cast_tkn(t_dlist *elem);
void			consume_token(t_parser *parser);
void			rollback_token(t_parser *parser);
/* parser.c */

t_ast_tree_node	*parse_from_str(char *str);

/* stack.c */

t_dlist			*push_stack(t_parser *parser, t_parse_stack *stack,
					void *content);
void			pop_stack(t_parse_stack *stack, size_t times);

/* pushnstack.c */

int				assemble_out_stack_top(t_parser *parser, size_t npop_op,
					bool force_pop);
int				handle_cmd_start(t_parser *parser);
int				handle_cmd_end(t_parser *parser);

/* pushnstack_utils.c */

bool			check_opening_prt(t_parser *parser);
bool			is_top_an_operator(t_parser parser);
bool			check_tkn_after_prt(t_parser *parser);

/* args.c */

t_arg			*new_arg(char *value, t_token_type token_type, bool dup);
void			free_arg(void *parg);
t_arg			*add_arg_to_list(t_parser *parser, t_dlist **args,
					t_token_type type);

/* node_expansion.c */

t_ast_tree_node	*apply_expansion_on_node(t_ast_tree_node *root,
					t_minishell *minishell);

#endif
