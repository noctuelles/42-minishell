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

# define STR_ERR_UNEXPECTED_TOKEN            "unexpected token"
# define STR_ERR_EXPECTED_COMMAND            "expected command"
# define STR_ERR_UNEXPECTED_IO_TOKEN         "expected filename for redirection"
# define STR_ERR_UNEXPECTED_IO_HEREDOC_TOKEN "expected here-doc delimiter"
# define STR_SYNTAX_ERROR                    "syntax error"

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
	NO_CMD = -1
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
	t_token				*curr_tkn;
	t_parser_errcode	errcode;
	t_parse_stack		output_stack;
	t_parse_stack		op_stack;
}	t_parser;

/* simple_command.c */

bool	is_a_redirection(t_token_type type);

/* parser_utils.c */

void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode);

/* parser.c */

t_ast_tree_node	*parse_from_str(char *str);

/* Prototype for each production rules : */

t_ast_tree_node	*pipeline(t_parser *parser);
t_ast_tree_node *simple_cmd(t_parser *parser);

/* stack.c */

t_dlist			*push_stack(t_parser *parser, t_parse_stack *stack,
		void *content);
void	pop_stack(t_parse_stack *stack, size_t times);
t_token_type	*new_token_type(t_token_type type);

/* pushnstack.c */

int	assemble_out_stack_top(t_parser *parser, size_t npop_op, bool force_pop);
int	handle_cmd_start(t_parser *parser);
int	handle_cmd_end(t_parser *parser);

/* pushnstack_utils.c */

t_token_type	curr_type(t_parser parser);
t_token			*cast_tkn(t_dlist *elem);
void			consume_token(t_parser *parser);
void			rollback_token(t_parser *parser);

/* args.c */


t_arg	*new_arg(char *value, t_token_type token_type, bool dup);
void	free_arg(void *parg);
t_arg	*add_arg_to_list(t_parser *parser, t_dlist **args, t_token_type type);

void	ast_print_tree(char *prefix, t_ast_tree_node *node, bool is_left);

#endif
