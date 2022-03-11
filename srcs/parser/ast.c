/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/11 14:44:42 by plouvel          ###   ########.fr       */
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

const char NODE_STR_EQU[][100] = {
	"PIPELINE",
	"SIMPLE_COMMAND",
	"SIMPLE_EMPTY_COMMAND",
	"SIMPLE_IMMEDIATE_COMMAND",
	"COMMAND_PREFIX",
	"COMMAND_SUFFIX",
	"REDIRECT_STDIN",
	"REDIRECT_FILE",
	"REDIRECT_FILE_APPEND",
	"REDIRECT_FILE_HERE_DOC",
	"IO",
	"RD_OUT",
	"RD_IN",
	"RD_HERE"
};

void	ast_tree_apply_preorder(t_ast_tree_node *root)
{
	if (root->left != NULL)
	{
		printf("%s", NODE_STR_EQU[root->type]);
		printf("->");
		ast_tree_apply_preorder(root->left);
	}
	if (root->right != NULL)
	{
		printf("%s", NODE_STR_EQU[root->type]);
		printf("->");
		ast_tree_apply_preorder(root->right);
	}
	if (root->right == NULL && root->left == NULL)
	{
		printf(";\n");
	}
}

void	ast_tree_print_graph(t_ast_tree_node *root)
{
	puts("digraph G {");
	ast_tree_apply_preorder(root);
	puts("}");
}
void	ast_tree_delete_node(t_ast_tree_node *node)
{
	if (node->left != NULL)
		ast_tree_delete_node(node->left);
	if (node->right != NULL)
		ast_tree_delete_node(node->right);
	free(node);
}
