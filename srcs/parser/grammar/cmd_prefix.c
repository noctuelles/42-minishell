/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:53:44 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/08 18:47:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*CMD_PREFIX(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (call_production(parser, &CMD_PREFIX1, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &CMD_PREFIX2, &rslt, TRUE) != NULL)
		return (rslt);
	puts("prefix failed");
	return (NULL);
}

t_ast_tree_node	*CMD_PREFIX1(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*cmd_prefix;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &IO_REDIRECT, &io_redirect, FALSE) == NULL)
		return (NULL);
	if (call_production(parser, &CMD_PREFIX, &cmd_prefix, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_PREFIX_IO);
	if (rslt)
		return (NULL);
	ast_tree_attach(rslt, io_redirect, cmd_prefix);
	return (rslt);
}

t_ast_tree_node	*CMD_PREFIX2(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &IO_REDIRECT, &io_redirect, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_PREFIX_IO);
	if (rslt)
		return (NULL);
	ast_tree_attach(rslt, io_redirect, NULL);
	return (rslt);
}
