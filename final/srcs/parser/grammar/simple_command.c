/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/12 14:45:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*SIMPLE_CMD(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &SIMPLE_CMD1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &SIMPLE_CMD2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &SIMPLE_CMD3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &SIMPLE_CMD4, &node, save) != NULL)
		return (node);
	if (call_production(parser, &SIMPLE_CMD5, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*SIMPLE_CMD1(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, IO_LIST, &io_list) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, io_list, NULL, NO_ERR));
	if (call_term(parser, CMD_SUFFIX, &cmd_suffix) == NULL)
		return (quit_production(parser, io_list, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, io_list, cmd_suffix, ERR_MALLOC));
	ast_tree_attach(rslt, io_list, cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD2(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, &IO_LIST, &io_list) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, io_list, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, io_list, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, io_list, NULL);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD3(t_parser *parser)
{
	return (IO_LIST(parser));
}

t_ast_tree_node	*SIMPLE_CMD4(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*rslt;

	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (NULL);
	if (call_term(parser, &CMD_SUFFIX, &cmd_suffix) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, cmd_suffix, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, NULL, cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD5(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*rslt;

	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (NULL);
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND_IMMEDIATE);
	if (!rslt)
		return (quit_production(parser, NULL, NULL, ERR_MALLOC));
	return (rslt);
}
