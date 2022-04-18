/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:54:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 18:41:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

t_ast_tree_node	*ast_tree_create_node(t_dlist *args, t_node_type type)
{
	t_ast_tree_node	*node;

	node = (t_ast_tree_node *) malloc(sizeof(t_ast_tree_node));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->args = args;
	node->type = type;
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

void	ast_tree_delete_node(void *node)
{
	t_ast_tree_node	*tree_node;

	tree_node = (t_ast_tree_node *) node;
	if (tree_node->left != NULL)
		ast_tree_delete_node(tree_node->left);
	if (tree_node->right != NULL)
		ast_tree_delete_node(tree_node->right);
	if (tree_node->args != NULL)
		ft_dlstclear(&tree_node->args, free_arg);
	free(tree_node);
}

/*static void iter_args(void *parg)
{
	t_arg	*arg;

	arg = parg;
	if (arg->type == ARG_REDIRECT_FILE)
		fputs("'>' ", stdout); 
	if (arg->type == ARG_REDIRECT_STDIN)
		fputs("'<' ", stdout); 
	if (arg->type == ARG_REDIRECT_FILE_APPEND)
		fputs("'>>' ", stdout); 
	if (arg->type == ARG_REDIRECT_HERE_DOC)
		fputs("'<<' ", stdout); 
	printf("\"%s\"   ", arg->value);
}*/

/*
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
		if (node->args)
		{
			ft_dlstiter(node->args, iter_args);
			fputs("\n", stdout);
		}
		else
		{
			if (node->type == NODE_LOGICAL_AND)
				printf("&&\n");
			else if (node->type == NODE_LOGICAL_OR)
				printf("||\n");
			else if (node->type == NODE_PIPE)
				printf("|\n");
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
*/
