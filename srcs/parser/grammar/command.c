/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:06:48 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:56:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*cmd(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, cmd1, &node, save) != NULL)
		return (node);
	if (call_production(parser, cmd2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*cmd1(t_parser *parser)
{
	return (simple_cmd(parser));
}

t_ast_tree_node	*cmd2(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (match(parser, T_OP_PRT, NULL) == FALSE)
		return (NULL);
	rslt = call_term(parser, and_or, &rslt);
	if (!rslt)
		return (quit_production(parser, NULL, NULL, NO_ERR));
	if (match(parser, T_CL_PRT, NULL) == FALSE)
		return (quit_production(parser, rslt, NULL, NO_ERR));
	if (rslt->type == NODE_LOGICAL_AND)
		rslt->type = NODE_PRIORITY_AND;
	else if (rslt->type == NODE_LOGICAL_OR)
		rslt->type = NODE_PRIORITY_OR;
	return (rslt);
}
