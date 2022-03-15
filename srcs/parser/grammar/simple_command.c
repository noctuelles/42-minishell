/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:49:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*simple_cmd(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &simple_cmd1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd4, &node, save) != NULL)
		return (node);
	if (call_production(parser, &simple_cmd5, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*simple_cmd1(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*node_cmd_suffix;
	t_ast_tree_node	*node_io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, io_list, &node_io_list) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, node_io_list, NULL, NO_ERR));
	if (call_term(parser, cmd_suffix, &node_cmd_suffix) == NULL)
		return (quit_production(parser, node_io_list, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, node_io_list, node_cmd_suffix,
				ERR_MALLOC));
	ast_tree_attach(rslt, node_io_list, node_cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*simple_cmd2(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*node_io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, io_list, &node_io_list) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, node_io_list, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, node_io_list, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, node_io_list, NULL);
	return (rslt);
}

t_ast_tree_node	*simple_cmd3(t_parser *parser)
{
	return (io_list(parser));
}

t_ast_tree_node	*simple_cmd4(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*node_cmd_suffix;
	t_ast_tree_node	*rslt;

	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, NULL, NULL, ERR_EXCEPTED_COMMAND));
	if (call_term(parser, cmd_suffix, &node_cmd_suffix) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, node_cmd_suffix, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, NULL, node_cmd_suffix);
	return (rslt);
}
