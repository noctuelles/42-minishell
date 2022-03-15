/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:58:33 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

t_ast_tree_node	*parse_from_lexer(t_lexer *lexer)
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
			perror("minishell");
		else
			print_parse_exception(get_parse_error(parser.errcode),
				lexer->tkns[parser.lex_idx - 1].val);
	}
	return (root);
}
