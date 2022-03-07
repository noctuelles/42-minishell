/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:09:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/07 18:07:59 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*PIPELINE(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (call_production(parser, &PIPELINE1, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &PIPELINE2, &rslt, TRUE) != NULL)
		return (rslt);
	return (quit_production(parser, NULL, NULL, ERR_SYNTAX));
}

/* PIPELINE1() production rule no 1. */

t_ast_tree_node	*PIPELINE1(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;
	t_ast_tree_node	*pipe_node;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &SIMPLE_CMD, &cmd_node, FALSE) == NULL)
		return (NULL);
	if (match(parser, T_PIPE, NULL) == FALSE)
		return (quit_production(parser, cmd_node, NULL, NO_ERR));
	if (call_production(parser, &PIPELINE, &pipe_node, FALSE) == NULL)
		return (quit_production(parser, cmd_node, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_PIPE);
	if (!rslt)
		return (quit_production(parser, cmd_node, pipe_node, ERR_MALLOC));
	ast_tree_attach(rslt, cmd_node, pipe_node);
	return (rslt);
}

t_ast_tree_node	*PIPELINE2(t_parser *parser)
{
	return (SIMPLE_CMD(parser));
}
