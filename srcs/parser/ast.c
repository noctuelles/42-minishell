/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:10:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/11 11:10:37 by dhubleur         ###   ########.fr       */
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
	if (node->value != NULL)
		free(node->value);
	free(node);
}
