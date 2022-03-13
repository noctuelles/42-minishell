/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/13 21:11:21 by dhubleur         ###   ########.fr       */
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
	"NODE_PIPE",
	"NODE_COMMAND_SUBSHELL",
	"NODE_COMMAND",
	"NODE_EMPTY_COMMAND",
	"NODE_IO_LIST",
	"NODE_COMMAND_IMMEDIATE",
	"NODE_COMMAND_PREFIX",
	"NODE_COMMAND_SUFFIX",
	"NODE_IO_REDIRECT_STDIN",
	"NODE_IO_REDIRECT_FILE",
	"NODE_IO_REDIRECT_FILE_APPEND",
	"NODE_IO_REDIRECT_HERE_DOC",
	"NODE_IO",
	"NODE_RD_OUT",
	"NODE_RD_IN",
	"NODE_RD_HERE"
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
