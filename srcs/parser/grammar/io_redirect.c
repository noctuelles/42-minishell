/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:09:20 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:55:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*io_redirect(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &io_redirect1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &io_redirect2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &io_redirect3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &io_redirect4, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*io_redirect1(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_LESS, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (quit_production(parser, NULL, NULL, ERR_UNEXCEPTED_IO_TOKEN));
	rslt = ast_tree_create_node(filename, NODE_io_redirect_STDIN);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*io_redirect2(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_GRT, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (quit_production(parser, NULL, NULL, ERR_UNEXCEPTED_IO_TOKEN));
	rslt = ast_tree_create_node(filename, NODE_io_redirect_FILE);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*io_redirect3(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_DGRT, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (quit_production(parser, NULL, NULL, ERR_UNEXCEPTED_IO_TOKEN));
	rslt = ast_tree_create_node(filename, NODE_io_redirect_FILE_APPEND);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*io_redirect4(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_DLESS, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (quit_production(parser, NULL, NULL,
				ERR_UNEXCEPTED_IO_HEREDOC_TOKEN));
	rslt = ast_tree_create_node(filename, NODE_io_redirect_HERE_DOC);
	if (!rslt)
		return (NULL);
	return (rslt);
}
