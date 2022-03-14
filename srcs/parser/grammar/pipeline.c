/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:09:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/14 17:19:43 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*PIPELINE(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &PIPELINE1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &PIPELINE2, &node, save) != NULL)
		return (node);
	return (NULL);
}

/* PIPELINE1() production rule no 1. */

t_ast_tree_node	*PIPELINE1(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;
	t_ast_tree_node	*pipe_node;
	t_ast_tree_node	*rslt;

	if (call_term(parser, CMD, &cmd_node) == NULL)
		return (NULL);
	if (match(parser, T_PIPE, NULL) == FALSE)
		return (quit_production(parser, cmd_node, NULL, NO_ERR));
	if (call_term(parser, PIPELINE, &pipe_node) == NULL)
		return (quit_production(parser, cmd_node, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_PIPE);
	if (!rslt)
		return (quit_production(parser, cmd_node, pipe_node, ERR_MALLOC));
	ast_tree_attach(rslt, cmd_node, pipe_node);
	return (rslt);
}

t_ast_tree_node	*PIPELINE2(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	rslt = CMD(parser);
	/*if (rslt)
	{
		if (match(parser, T_NULL, NULL) == FALSE)
		{
			ast_tree_delete_node(rslt);
			return (NULL);
		}
	}*/
	return (rslt);
}
