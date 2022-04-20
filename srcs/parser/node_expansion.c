/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:43:46 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 12:49:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

/* iter() iterates throught the list tkns, by aplying to each of the element of
 * tkns the function f. */

static t_dlist	*iter(t_dlist **args, t_minishell *minishell, t_dlist *(*f)())
{
	t_arg	*arg;
	t_dlist	*elem;
	t_dlist	*next;

	elem = *args;
	while (elem)
	{
		next = elem->next;
		arg = (t_arg *) elem->content;
		elem = f(args, elem, arg, minishell);
		if (!elem && minishell->err)
			return (NULL);
		else if (elem != next)
			elem = elem->next;
	}
	return (*args);
}

t_ast_tree_node	*apply_expansion_on_node(t_ast_tree_node *root,
		t_minishell *minishell)
{
	t_ast_tree_node	*cmd_node;
	t_dlist			*new_args;

	if (root->type == NODE_PIPE)
	{
		cmd_node = root->left;
		if (!apply_expansion_on_node(root->right, minishell))
			return (NULL);
	}
	if (root->type == NODE_COMMAND)
		cmd_node = root;
	new_args = iter(&cmd_node->args, minishell, var_expansion);
	if (!new_args && minishell->err)
		return (NULL);
	cmd_node->args = new_args;
	new_args = iter(&cmd_node->args, minishell, wildcard_expansion);
	if (!new_args && minishell->err)
		return (NULL);
	cmd_node->args = new_args;
	if (minishell->ambiguous_redir)
	{
		ft_dlstclear(&root->args, free_arg);
		minishell->ambiguous_redir = false;
	}
	return (root);
}
