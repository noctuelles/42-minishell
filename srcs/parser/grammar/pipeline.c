/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:09:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/07 16:40:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*pipeline(t_parser *parser)
{
	t_ast_tree_node	*node;
	t_dlist			*save;

	save = parser->tkns;
	if (call_production(parser, &pipeline1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &pipeline2, &node, save) != NULL)
		return (node);
	return (NULL);
}

/* pipeline1() production rule no 1. */

t_ast_tree_node	*pipeline1(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;
	t_ast_tree_node	*pipe_node;
	t_ast_tree_node	*rslt;

	if (call_term(parser, simple_cmd, &cmd_node) == NULL)
		return (NULL);
	if (match(parser, T_PIPE, NULL) == FALSE)
		return (quit_production(parser, cmd_node, NULL, NO_ERR));
	if (call_term(parser, pipeline, &pipe_node) == NULL)
		return (quit_production(parser, cmd_node, NULL, ERR_EXPECTED_COMMAND));
	rslt = ast_tree_create_node(NULL, NODE_PIPE);
	if (!rslt)
		return (quit_production(parser, cmd_node, pipe_node, ERR_MALLOC));
	ast_tree_attach(rslt, cmd_node, pipe_node);
	return (rslt);
}

t_ast_tree_node	*pipeline2(t_parser *parser)
{
	return (simple_cmd(parser));
}
