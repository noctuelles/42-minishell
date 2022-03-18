/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/18 20:05:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static t_lexer	*lex_input(char *str)
{
	t_lexer	*lexer;
	int		ret_code;

	lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	ret_code = fill_lexer_from_str(lexer, str);
	if (ret_code != 0)
	{
		if (ret_code == ERR_MEM)
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
		else
		{
			if (lexer->idx == 0)
				ft_dprintf(STDERR_FILENO, STR_ERROR,
						get_lexer_error(ret_code));
			else
				ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
						get_lexer_error(ret_code),
						lexer->tkns[lexer->idx - 1].val);
		}
		free_lexer(lexer);
		lexer = NULL;
	}
	return (lexer);
}

static t_ast_tree_node	*parse_from_lexer(t_lexer *lexer)
{
	t_parser		parser;
	t_ast_tree_node	*root;

	parser.lexer = lexer;
	parser.lex_idx = 0;
	parser.errcode = NO_ERR;
	root = complete_cmd(&parser);
	if (!root)
	{
		if (parser.errcode == ERR_MALLOC)
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
		else
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
					get_parser_error(parser.errcode),
					lexer->tkns[parser.lex_idx - 1].val);
	}
	else
	{
		// Here we're doing variable expansion and removing all quote.
	}
	return (root);
}

t_ast_tree_node	*parse(char *str)
{
	t_lexer			*lexer;
	t_ast_tree_node	*ast_root;

	lexer = lex_input(str);
	if (!lexer)
		return (NULL);
	ast_root = parse_from_lexer(lexer);
	free_lexer(lexer);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}
