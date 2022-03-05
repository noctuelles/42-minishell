/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/05 20:02:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

t_ast_tree_node	*ast_tree_create_node(char *value, t_node_type type)
{
	t_ast_tree_node	*node;

	node = (t_ast_tree_node *) malloc(sizeof(t_ast_tree_node));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->type = type;
	node->value = value;
	return (NULL);
}

void	ast_tree_delete_node(t_ast_tree_node *node)
{
	if (node->left != NULL)
		ast_tree_delete_node(node->left);
	if (node->right != NULL)
		ast_tree_delete_node(node->right);
	free(node);
}
