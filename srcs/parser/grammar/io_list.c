/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:37:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/12 14:45:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*IO_LIST(t_parser *parser)
{
	t_ast_tree_node	*node;
	size_t			save;

	save = parser->lex_idx;
	if (call_production(parser, IO_LIST1, &node, save) != NULL)
		return (node);
	if (call_production(parser, IO_LIST2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*IO_LIST1(t_parser *parser)
{
	t_ast_tree_node	*io_redirection;
	t_ast_tree_node	*io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, IO_REDIRECT, &io_redirection) == NULL)
		return (NULL);
	if (call_term(parser, IO_LIST, &io_list) == NULL)
		return (quit_production(parser, io_redirection, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_IO_LIST); 
	if (!rslt)
		return (quit_production(parser, io_redirection, io_list, ERR_MALLOC));
	ast_tree_attach(rslt, io_redirection, io_list);
	return (rslt);
}

t_ast_tree_node	*IO_LIST2(t_parser *parser)
{
	return (IO_REDIRECT(parser));
}
