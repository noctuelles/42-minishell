/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:53:44 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/10 17:50:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*CMD_PREFIX(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &CMD_PREFIX1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &CMD_PREFIX2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*CMD_PREFIX1(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*cmd_prefix;
	t_ast_tree_node	*rslt;

	if (call_term(parser, &IO_REDIRECT, &io_redirect) == NULL)
		return (NULL);
	if (call_term(parser, &CMD_PREFIX, &cmd_prefix) == NULL)
		return (quit_production(parser, io_redirect, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_PREFIX);
	if (!rslt)
		return (quit_production(parser, io_redirect, cmd_prefix, NO_ERR));
	ast_tree_attach(rslt, io_redirect, cmd_prefix);
	return (rslt);
}

t_ast_tree_node	*CMD_PREFIX2(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*rslt;

	if (call_term(parser, &IO_REDIRECT, &io_redirect) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_PREFIX);
	if (!rslt)
		return (quit_production(parser, io_redirect, NULL, NO_ERR));
	ast_tree_attach(rslt, io_redirect, NULL);
	return (rslt);
}
