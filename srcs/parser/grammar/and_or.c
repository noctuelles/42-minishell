/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:54:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:57:24 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*and_or(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, and_or1, &node, save) != NULL)
		return (node);
	if (call_production(parser, and_or2, &node, save) != NULL)
		return (node);
	if (call_production(parser, and_or3, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*and_or1(t_parser *parser)
{
	t_ast_tree_node	*node_pipeline;
	t_ast_tree_node	*node_and_or;
	t_ast_tree_node	*rslt;

	if (call_term(parser, pipeline, &node_pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_AND, NULL) == FALSE)
		return (quit_production(parser, node_pipeline, NULL, NO_ERR));
	if (call_term(parser, and_or, &node_and_or) == NULL)
		return (quit_production(parser, node_pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_LOGICAL_AND);
	if (!rslt)
		return (quit_production(parser, node_pipeline, node_and_or,
				ERR_MALLOC));
	ast_tree_attach(rslt, node_pipeline, node_and_or);
	return (rslt);
}

t_ast_tree_node	*and_or2(t_parser *parser)
{
	t_ast_tree_node	*node_pipeline;
	t_ast_tree_node	*node_and_or;
	t_ast_tree_node	*rslt;

	if (call_term(parser, pipeline, &node_pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_OR, NULL) == FALSE)
		return (quit_production(parser, node_pipeline, NULL, NO_ERR));
	if (call_term(parser, and_or, &node_and_or) == NULL)
		return (quit_production(parser, node_pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_LOGICAL_OR);
	if (!rslt)
		return (quit_production(parser, node_pipeline, node_and_or,
				ERR_MALLOC));
	ast_tree_attach(rslt, node_pipeline, node_and_or);
	return (rslt);
}

t_ast_tree_node	*and_or3(t_parser *parser)
{
	return (pipeline(parser));
}
