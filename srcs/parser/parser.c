/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:43:28 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 18:43:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include "parser.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void	*quit_parsing(t_parser *parser)
{
	if (curr_type(*parser) == T_NULL)
		rollback_token(parser);
	if (parser->errcode != ERR_MALLOC)
	{
		if (parser->last_used_tkn)
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
				get_parser_error(parser->errcode), parser->last_used_tkn->val);
		else
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
				get_parser_error(parser->errcode), parser->curr_tkn->val);
	}
	else
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
	ft_dlstclear(&parser->op_stack.cnt, NULL);
	ft_dlstclear(&parser->output_stack.cnt, ast_tree_delete_node);
	return (NULL);
}

static bool	is_correct_start_tkn(t_parser *parser)
{
	t_token_type	type;

	type = curr_type(*parser);
	if (type == T_OP_PRT || type == T_WORD || is_a_redirection(type))
		return (true);
	set_parser_errcode(parser, ERR_EXPECTED_COMMAND);
	return (false);
}

static t_ast_tree_node	*do_parse(t_parser *parser)
{
	t_ast_tree_node	*root;

	while (curr_type(*parser) != T_NULL)
	{
		if (!is_correct_start_tkn(parser))
			return (quit_parsing(parser));
		if (handle_cmd_start(parser) == -1)
			return (quit_parsing(parser));
		if (handle_cmd_end(parser) == -1)
			return (quit_parsing(parser));
	}
	if (assemble_out_stack_top(parser, 1, false) == -1)
		return (quit_parsing(parser));
	if (parser->output_stack.top)
	{
		root = (t_ast_tree_node *) parser->output_stack.top->content;
		pop_stack(&parser->output_stack, 1);
		return (root);
	}
	else
		return (NULL);
}

/* parse_from_tkns() returns a valid AST tree for the given command.
 * If no command was found or an error occured, parse returns NULL,
 * while freeing everything in use including the tokens.
 * The tokens are freed no mather what. */

static t_ast_tree_node	*parse_from_tkns(t_dlist **tkns)
{
	t_parser		parser;
	t_ast_tree_node	*ast_root;

	ft_memset(&parser, 0, sizeof(t_parser));
	parser.tkns = *tkns;
	parser.curr_tkn = (t_token *) parser.tkns->content;
	ast_root = do_parse(&parser);
	ft_dlstclear(tkns, free_token);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}

/* parse_from_str() returns a valid AST tree if str is following the minishell
 * grammar.
 * If no cmd was found in str or and error occured, the function returns
 * NULL.*/

t_ast_tree_node	*parse_from_str(char *str)
{
	t_dlist			*tkns;
	t_ast_tree_node	*ast_root;

	tkns = lex_str(str);
	if (!tkns)
		return (NULL);
	ast_root = parse_from_tkns(&tkns);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}
