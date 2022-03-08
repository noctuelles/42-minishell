/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/08 18:44:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_ast_tree_node	*SIMPLE_CMD(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (call_production(parser, &SIMPLE_CMD1, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &SIMPLE_CMD2, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &SIMPLE_CMD3, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &SIMPLE_CMD4, &rslt, TRUE) != NULL)
		return (rslt);
	if (call_production(parser, &SIMPLE_CMD5, &rslt, TRUE) != NULL)
		return (rslt);
	return (NULL);
}

t_ast_tree_node	*SIMPLE_CMD1(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*cmd_prefix;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &CMD_PREFIX, &cmd_prefix, FALSE) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, cmd_prefix, NULL, NO_ERR));
	if (call_production(parser, &CMD_SUFFIX, &cmd_suffix, FALSE) == NULL)
		return (quit_production(parser, cmd_prefix, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, cmd_prefix, cmd_suffix, NO_ERR));
	ast_tree_attach(rslt, cmd_prefix, cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD2(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*cmd_prefix;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &CMD_PREFIX, &cmd_prefix, FALSE) == NULL)
		return (NULL);
	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, cmd_prefix, NULL, NO_ERR));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, cmd_prefix, NULL, NO_ERR));
	ast_tree_attach(rslt, cmd_prefix, NULL);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD3(t_parser *parser)
{
	t_ast_tree_node	*cmd_prefix;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &CMD_PREFIX, &cmd_prefix, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_EMPTY_COMMAND);
	if (!rslt)
		return (quit_production(parser, cmd_prefix, NULL, NO_ERR));
	ast_tree_attach(rslt, cmd_prefix, NULL);
	return (rslt);
}

t_ast_tree_node	*SIMPLE_CMD4(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*rslt;

	if (match(parser, T_WORD, &cmd_name) == FALSE)
	{
		puts("failed matching");
		return (NULL);
	}
	if (call_production(parser, &CMD_SUFFIX, &cmd_suffix, FALSE) == NULL)
	{
		puts("failed suffix");
		printf("cmd_name : %s\n", cmd_name);
		return (NULL);
	}
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, NULL, cmd_suffix, NO_ERR));
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
		return (quit_production(parser, NULL, NULL, NO_ERR));
	return (rslt);
}
