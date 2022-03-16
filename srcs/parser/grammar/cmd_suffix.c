/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:20 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/16 14:51:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"
#include <stdlib.h>

t_ast_tree_node	*cmd_suffix(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;
	save = parser->lex_idx;
	if (call_production(parser, &cmd_suffix1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &cmd_suffix2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &cmd_suffix3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &cmd_suffix4, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*cmd_suffix1(t_parser *parser)
{
	t_ast_tree_node	*node_io_list;
	t_ast_tree_node	*node_cmd_suffix;
	t_ast_tree_node	*rslt;

	if (call_term(parser, io_list, &node_io_list) == NULL)
		return (NULL);
	if (call_term(parser, cmd_suffix, &node_cmd_suffix) == NULL)
		return (quit_production(parser, node_io_list, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, node_io_list, node_cmd_suffix, NO_ERR));
	ast_tree_attach(rslt, node_io_list, node_cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*cmd_suffix2(t_parser *parser)
{
	return (io_list(parser));
}

t_ast_tree_node	*cmd_suffix3(t_parser *parser)
{
	t_ast_tree_node	*node_cmd_suffix;
	t_ast_tree_node	*rslt;
	char			*arg;

	if (match(parser, T_WORD, &arg) == FALSE)
		return (NULL);
	if (call_term(parser, cmd_suffix, &node_cmd_suffix) == NULL)
	{
		free(arg);
		return (NULL);
	}
	rslt = ast_tree_create_node(arg, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, node_cmd_suffix, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, node_cmd_suffix, NULL);
	return (rslt);
}

t_ast_tree_node	*cmd_suffix4(t_parser *parser)
{
	t_ast_tree_node	*rslt;
	char			*arg;

	if (match(parser, T_WORD, &arg) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(arg, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, NULL, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, NULL, NULL);
	return (rslt);
}
