/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/12 20:00:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void	ast_print_tree(char *prefix, t_ast_tree_node *node, bool is_left)
{
	char	*new_prefix;

	if (node)
	{
		fputs(prefix, stdout);
		if (is_left)
			fputs("├──", stdout);
		else
			fputs("└──", stdout);
		if (node->value)
		{
			if (node->type == NODE_IO_REDIRECT_STDIN)
				printf("< ");
			if (node->type == NODE_IO_REDIRECT_FILE)
				printf("> ");
			if (node->type == NODE_IO_REDIRECT_FILE_APPEND)
				printf(">> ");
			if (node->type == NODE_IO_REDIRECT_HERE_DOC)
				printf("<< ");
			printf("%s\n", node->value);
		}
		else
		{
			if (node->type == NODE_LOGICAL_AND)
				printf("&&\n");
			else if (node->type == NODE_LOGICAL_OR)
				printf("||\n");
			else if (node->type == NODE_PIPE)
				printf("|\n");
			else if (node->type == NODE_IO_LIST)
				printf("<>");
		}
		new_prefix = (char *) malloc((ft_strlen(prefix) + 8 + 1) * sizeof(char));
		new_prefix[0] = '\0';
		ft_strcat(new_prefix, prefix);
		if (is_left)
			ft_strcat(new_prefix, "|    ");
		else
			ft_strcat(new_prefix, "     ");
		ast_print_tree(new_prefix, node->left, true);
		ast_print_tree(new_prefix, node->right, false);
	}
}

void	ast_tree_delete_node(void *node)
{
	t_ast_tree_node	*tree_node;

	tree_node = (t_ast_tree_node *) node;
	if (tree_node->left != NULL)
		ast_tree_delete_node(tree_node->left);
	if (tree_node->right != NULL)
		ast_tree_delete_node(tree_node->right);
	if (tree_node->value != NULL)
		free(tree_node->value);
	free(tree_node);
}
