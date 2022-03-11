/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:10:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/11 23:34:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*CMD(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, CMD1, &node, save) != NULL)
		return (node);
	if (call_production(parser, CMD2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*CMD1(t_parser *parser)
{
	t_ast_tree_node	*cmd;
	t_ast_tree_node	*rslt;

	if (match(parser, T_OP_PRT, NULL) == FALSE)
		return (NULL);
	if (call_term(parser, CMD, &cmd) == NULL)
		return (NULL);
	if (match(parser, T_CL_PRT, NULL) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUBSHELL); 
	if (!rslt)
		return (NULL);
	ast_tree_attach(rslt, cmd, NULL);
	return (rslt);
}

t_ast_tree_node	*CMD2(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	rslt = SIMPLE_CMD(parser);
	/*if (rslt)
	{
		if (match(parser, T_NULL, NULL) == FALSE)
		{
			return (NULL);
		}
	}*/
	return (rslt);
}
