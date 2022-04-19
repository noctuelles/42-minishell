/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 22:23:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include <readline/readline.h>

static bool	is_a_logical_node(t_ast_tree_node *node)
{
	if (node->type == NODE_LOGICAL_AND || node->type == NODE_LOGICAL_OR)
		return (true);
	else
		return (false);
}

bool	is_a_pipeline_node(t_ast_tree_node *node)
{
	if (node->type == NODE_COMMAND || node->type == NODE_PIPE)
		return (true);
	else
		return (false);
}

static bool	continue_exec(t_minishell *minishell, t_node_type type)
{
	if (type == NODE_LOGICAL_AND)
	{
		if (minishell->last_ret == 0)
			return (true);
	}
	if (type == NODE_LOGICAL_OR)
	{
		if (minishell->last_ret != 0)
			return (true);
	}
	return (false);
}

void	parse_and_or(t_ast_tree_node *node, t_minishell *minishell)
{
	if (node->left == NULL || node->right == NULL)
		return ;
	if (is_a_logical_node(node->left))
		parse_and_or(node->left, minishell);
	else if (is_a_pipeline_node(node->left))
		minishell->last_ret = execute_pipeline(node->left, minishell) % 256;
	if (continue_exec(minishell, node->type))
	{
		if (is_a_logical_node(node->right))
			parse_and_or(node->right, minishell);
		else if (is_a_pipeline_node(node->right))
			minishell->last_ret
				= execute_pipeline(node->right, minishell) % 256;
	}
}
