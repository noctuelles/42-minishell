/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:20 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/08 18:56:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*CMD_SUFFIX(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	if (call_production(parser, &CMD_SUFFIX1, &rslt, TRUE) != NULL)
	{
		puts("CMD_SUFFIX1 suceeded !");
		return (rslt);
	}
	else
		puts("CMD_SUFFIX1 failed !");

	if (call_production(parser, &CMD_SUFFIX2, &rslt, TRUE) != NULL)
	{
		puts("CMD_SUFFIX2 suceeded !");
		return (rslt);
	}
	else
		puts("CMD_SUFFIX2 failed !");

	if (call_production(parser, &CMD_SUFFIX3, &rslt, TRUE) != NULL)
	{
		puts("CMD_SUFFIX3 suceeded !");
		return (rslt);
	}
	else
		puts("CMD_SUFFIX3 failed !");
	if (call_production(parser, &CMD_SUFFIX4, &rslt, TRUE) != NULL)
	{
		puts("CMD_SUFFIX4 suceeded !");
		return (rslt);
	}
	else
		puts("CMD_SUFFIX4 failed !");
	return (NULL);
}

t_ast_tree_node	*CMD_SUFFIX1(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &IO_REDIRECT, &io_redirect, FALSE) == NULL)
		return (NULL);
	if (call_production(parser, &CMD_SUFFIX, &cmd_suffix, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUFFIX_IO);
	if (rslt)
		return (NULL);
	ast_tree_attach(rslt, io_redirect, cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*CMD_SUFFIX2(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*rslt;

	if (call_production(parser, &IO_REDIRECT, &io_redirect, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUFFIX_IO);
	if (rslt)
		return (NULL);
	ast_tree_attach(rslt, io_redirect, NULL);
	return (rslt);
}

t_ast_tree_node	*CMD_SUFFIX3(t_parser *parser)
{
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*rslt;
	char			*arg;

	if (match(parser, T_WORD, &arg) == FALSE)
		return (NULL);
	if (call_production(parser, CMD_SUFFIX, &cmd_suffix, FALSE) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(arg, NODE_COMMAND_SUFFIX_WORD_LIST);
	if (!rslt)
		return (NULL);
	ast_tree_attach(rslt, cmd_suffix, NULL);
	return (rslt);
}

t_ast_tree_node	*CMD_SUFFIX4(t_parser *parser)
{
	t_ast_tree_node	*rslt;
	char			*arg;

	if (match(parser, T_WORD, &arg) == FALSE)
		return (NULL);
	printf("arg : %s\n", arg);
	rslt = ast_tree_create_node(arg, NODE_COMMAND_SUFFIX_WORD);
	if (!rslt)
		return (NULL);
	ast_tree_attach(rslt, NULL, NULL);
	return (rslt);
}
