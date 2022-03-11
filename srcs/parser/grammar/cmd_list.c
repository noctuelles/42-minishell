/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:54:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/11 17:41:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*CMD_LIST(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;
	
	save = parser->lex_idx;
	if (call_production(parser, CMD_LIST1, &node, save) != NULL)
		return (node);
	if (call_production(parser, CMD_LIST2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*CMD_LIST1(t_parser *parser)
{
	t_ast_tree_node	*pipeline;
	t_ast_tree_node	*cmd_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, PIPELINE, &pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_AND, NULL) == FALSE)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	if (call_term(parser, CMD_LIST, &cmd_list) == NULL)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_LIST_AND); 
	if (!rslt)
		return (quit_production(parser, pipeline, cmd_list, ERR_MALLOC));
	ast_tree_attach(rslt, pipeline, cmd_list);
	return (rslt);
}

t_ast_tree_node	*CMD_LIST2(t_parser *parser)
{
	t_ast_tree_node	*pipeline;
	t_ast_tree_node	*cmd_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, PIPELINE, &pipeline) == NULL)
		return (NULL);
	if (match(parser, T_LOG_OR, NULL) == FALSE)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	if (call_term(parser, CMD_LIST, &cmd_list) == NULL)
		return (quit_production(parser, pipeline, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_LIST_OR); 
	if (!rslt)
		return (quit_production(parser, pipeline, cmd_list, ERR_MALLOC));
	ast_tree_attach(rslt, pipeline, cmd_list);
	return (rslt);
}

t_ast_tree_node	*CMD_LIST3(t_parser *parser)
{
	return (PIPELINE(parser));
}
