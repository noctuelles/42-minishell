/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/13 17:52:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include <stdlib.h>

t_ast_tree_node	*simple_cmd(t_parser *parser)
{
	t_ast_tree_node	*node;
	t_dlist			*save;

	save = parser->tkns;
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
	{
		free(cmd_name);
		return (quit_production(parser, node_io_list, NULL, NO_ERR));
	}
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
		return (quit_production(parser, NULL, NULL, ERR_EXPECTED_COMMAND));
	if (call_term(parser, cmd_suffix, &node_cmd_suffix) == NULL)
	{
		free(cmd_name);
		return (NULL);
	}
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
		return (quit_production(parser, node_cmd_suffix, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, NULL, node_cmd_suffix);
	return (rslt);
}

t_arg	*new_arg(char *value, t_token_type token_type)
{
	t_arg		*arg;
	char		*arg_value;
	t_arg_type	arg_type;

	if (token_type == T_GRT)
		arg_type = ARG_REDIRECT_FILE;
	else if (token_type == T_LESS)
		arg_type = ARG_REDIRECT_STDIN;
	else if (token_type == T_DGRT)
		arg_type = ARG_REDIRECT_FILE_APPEND;
	else if (token_type == T_DLESS)
		arg_type = ARG_REDIRECT_HERE_DOC;
	else
		arg_type = ARG_WORD;
	arg = (t_arg *) malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg_value = ft_strdup(value);
	if (!arg_value)
	{
		free(arg);
		return (NULL);
	}
	arg->type = arg_type;
	arg->value = arg_value;
	return (arg);
}

t_ast_tree_node *simple_command(t_parser *parser)
{
	while (true)
	{
		if (is_a_redirection(*parser))
		{
			parser->tkns = parser->tkns->next;
			if (cast_tkn(parser->tkns)->type == T_WORD)
			{

			}
			else
			{
				// ca va pas il y a une erreur
			}
		}
		if (cast_tkn(parser->tkns)->type == T_WORD)
		{

		}
		else
			break ;
	}
}
