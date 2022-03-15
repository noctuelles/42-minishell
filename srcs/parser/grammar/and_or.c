/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:54:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 10:29:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*AND_OR(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, AND_OR1, &node, save) != NULL)
		return (node);
	if (call_production(parser, AND_OR2, &node, save) != NULL)
		return (node);
	if (call_production(parser, AND_OR3, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*AND_OR1(t_parser *parser)
{
	t_ast_tree_node	*pipeline;
	t_ast_tree_node	*and_or;
	t_ast_tree_node	*rslt;

	if (call_term(parser, PIPELINE, &pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_AND, NULL) == FALSE)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	if (call_term(parser, AND_OR, &and_or) == NULL)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_LOGICAL_AND);
	if (!rslt)
		return (quit_production(parser, pipeline, and_or, ERR_MALLOC));
	ast_tree_attach(rslt, pipeline, and_or);
	return (rslt);
}

t_ast_tree_node	*AND_OR2(t_parser *parser)
{
	t_ast_tree_node	*pipeline;
	t_ast_tree_node	*and_or;
	t_ast_tree_node	*rslt;

	if (call_term(parser, PIPELINE, &pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_OR, NULL) == FALSE)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	if (call_term(parser, AND_OR, &and_or) == NULL)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_LOGICAL_OR);
	if (!rslt)
		return (quit_production(parser, pipeline, and_or, ERR_MALLOC));
	ast_tree_attach(rslt, pipeline, and_or);
	return (rslt);
}

t_ast_tree_node	*AND_OR3(t_parser *parser)
{
	return(PIPELINE(parser));
}
