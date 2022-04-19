/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 18:07:13 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include <readline/readline.h>

void	parse_and_or(t_ast_tree_node *node, t_minishell *minishell)
{
	if (node->left == NULL || node->right == NULL)
		return ;
	if (node->left->type == NODE_LOGICAL_AND
		|| node->left->type == NODE_LOGICAL_OR)
		parse_and_or(node->left, minishell);
	else if (node->left->type == NODE_COMMAND || node->left->type == NODE_PIPE)
		minishell->last_ret = execute_pipeline(node->left, minishell) % 256;
	if ((minishell->last_ret == 0 && node->type == NODE_LOGICAL_AND)
		|| (minishell->last_ret != 0 && node->type == NODE_LOGICAL_OR))
	{
		if (node->right->type == NODE_LOGICAL_AND
			|| node->right->type == NODE_LOGICAL_OR)
			parse_and_or(node->right, minishell);
		else if (node->right->type == NODE_COMMAND
			|| node->right->type == NODE_PIPE)
			minishell->last_ret
				= execute_pipeline(node->right, minishell) % 256;
	}
}
