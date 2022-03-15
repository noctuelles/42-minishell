/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:59:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

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
	return (node);
}

t_ast_tree_node	*ast_tree_attach(t_ast_tree_node *root, t_ast_tree_node *left,
		t_ast_tree_node *right)
{
	if (!root)
		return (NULL);
	root->left = left;
	root->right = right;
	return (root);
}

void	ast_tree_delete_node(t_ast_tree_node *node)
{
	if (node->left != NULL)
		ast_tree_delete_node(node->left);
	if (node->right != NULL)
		ast_tree_delete_node(node->right);
	free(node);
}
