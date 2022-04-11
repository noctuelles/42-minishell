/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:37:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/11 11:08:34 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*io_list(t_parser *parser)
{
	t_ast_tree_node	*node;
	t_dlist			*save;

	save = parser->tkns;
	if (call_production(parser, io_list1, &node, save) != NULL)
		return (node);
	if (call_production(parser, io_list2, &node, save) != NULL)
		return (node);
	return (NULL);
}

t_ast_tree_node	*io_list1(t_parser *parser)
{
	t_ast_tree_node	*node_io_redirect;
	t_ast_tree_node	*node_io_list;
	t_ast_tree_node	*rslt;

	if (call_term(parser, io_redirect, &node_io_redirect) == NULL)
		return (NULL);
	if (call_term(parser, io_list, &node_io_list) == NULL)
		return (quit_production(parser, node_io_redirect, NULL, NO_ERR));
	rslt = ast_tree_create_node(NULL, NODE_IO_LIST);
	if (!rslt)
		return (quit_production(parser, node_io_redirect, node_io_list,
				ERR_MALLOC));
	ast_tree_attach(rslt, node_io_redirect, node_io_list);
	return (rslt);
}

t_ast_tree_node	*io_list2(t_parser *parser)
{
	return (io_redirect(parser));
}
