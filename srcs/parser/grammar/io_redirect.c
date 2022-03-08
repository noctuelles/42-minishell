/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:09:20 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/08 21:44:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*IO_REDIRECT(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (call_production(parser, &IO_REDIRECT1, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &IO_REDIRECT2, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &IO_REDIRECT3, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &IO_REDIRECT4, &rslt, TRUE) != NULL)
		return (rslt);
	return (NULL);
}

t_ast_tree_node	*IO_REDIRECT1(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_LESS, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(filename, NODE_IO_REDIRECT_STDIN);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*IO_REDIRECT2(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_GRT, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(filename, NODE_IO_REDIRECT_FILE);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*IO_REDIRECT3(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_DGRT, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(filename, NODE_IO_REDIRECT_FILE_APPEND);
	if (!rslt)
		return (NULL);
	return (rslt);
}

t_ast_tree_node	*IO_REDIRECT4(t_parser *parser)
{
	char			*filename;
	t_ast_tree_node	*rslt;

	if (match(parser, T_DLESS, NULL) == FALSE)
		return (NULL);
	if (match(parser, T_WORD, &filename) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(filename, NODE_IO_REDIRECT_HERE_DOC);
	if (!rslt)
		return (NULL);
	return (rslt);
}
