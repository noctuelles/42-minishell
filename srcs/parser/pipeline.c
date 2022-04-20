/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:09:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 02:18:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

static bool	is_valid_terminal(t_token_type type)
{
	if (type == T_NULL || type == T_LOG_AND || type == T_LOG_OR
		|| type == T_CL_PRT)
		return (true);
	else
		return (false);
}

static void	*clean(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode)
{
	if (left)
		ast_tree_delete_node(left);
	if (right)
		ast_tree_delete_node(right);
	if (errcode != ERR_KEEP)
		parser->errcode = errcode;
	return (NULL);
}

t_ast_tree_node	*pipeline(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;
	t_ast_tree_node	*pipe_node;
	t_ast_tree_node	*rslt;

	rslt = NULL;
	cmd_node = simple_cmd(parser);
	if (!cmd_node)
		return (NULL);
	if (curr_type(*parser) == T_PIPE)
	{
		consume_token(parser);
		pipe_node = pipeline(parser);
		if (!pipe_node)
			return (clean(parser, cmd_node, NULL, ERR_KEEP));
		rslt = ast_tree_create_node(NULL, NODE_PIPE);
		if (!rslt)
			return (clean(parser, cmd_node, pipe_node, ERR_MALLOC));
		ast_tree_attach(rslt, cmd_node, pipe_node);
	}
	else if (is_valid_terminal(curr_type(*parser)))
		rslt = cmd_node;
	else
		return (clean(parser, cmd_node, NULL, ERR_UNEXPECTED_TOKEN));
	return (rslt);
}
