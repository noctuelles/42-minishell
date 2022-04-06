/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/06 15:52:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static t_ast_tree_node	*parse_from_tkns(t_dlist *tkns)
{
	t_parser		parser;
	t_ast_tree_node	*root;

	parser.tkns = tkns;
	parser.errcode = NO_ERR;
	root = complete_cmd(&parser);
	if (!root)
	{
/*		if (parser.errcode == ERR_MALLOC)
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
		else
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
					get_parser_error(parser.errcode),
					lexer->tkns[parser.lex_idx - 1].val);*/
	}
	else
	{
		// Here we're doing variable expansion and removing all quote.
	}
	return (root);
}

t_ast_tree_node	*parse(t_dlist **tkns)
{
	t_ast_tree_node	*ast_root;

	ast_root = parse_from_tkns(*tkns);
	ft_dlstclear(tkns, free_token);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}
