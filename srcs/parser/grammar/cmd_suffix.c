/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:20 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/10 17:52:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*CMD_SUFFIX(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, &CMD_SUFFIX1, &node, save) != NULL)
		return (node);
	if (call_production(parser, &CMD_SUFFIX2, &node, save) != NULL)
		return (node);
	if (call_production(parser, &CMD_SUFFIX3, &node, save) != NULL)
		return (node);
	if (call_production(parser, &CMD_SUFFIX4, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*CMD_SUFFIX1(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*cmd_suffix;
	t_ast_tree_node	*rslt;

	if (call_term(parser, &IO_REDIRECT, &io_redirect) == NULL)
		return (NULL);
	if (call_term(parser, &CMD_SUFFIX, &cmd_suffix) == NULL)
		return (quit_production(parser, io_redirect, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, io_redirect, cmd_suffix, ERR_MALLOC));
	ast_tree_attach(rslt, io_redirect, cmd_suffix);
	return (rslt);
}

t_ast_tree_node	*CMD_SUFFIX2(t_parser *parser)
{
	t_ast_tree_node	*io_redirect;
	t_ast_tree_node	*rslt;

	if (call_term(parser, &IO_REDIRECT, &io_redirect) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(NULL, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, io_redirect, NULL, ERR_MALLOC));
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
	if (call_term(parser, CMD_SUFFIX, &cmd_suffix) == NULL)
		return (NULL);
	rslt = ast_tree_create_node(arg, NODE_COMMAND_SUFFIX);
	if (!rslt)
		return (quit_production(parser, cmd_suffix, NULL, ERR_MALLOC));
	ast_tree_attach(rslt, cmd_suffix, NULL);
	return (rslt);
}

t_ast_tree_node	*CMD_SUFFIX4(t_parser *parser)
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
