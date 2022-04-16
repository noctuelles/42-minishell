/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:43:46 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/16 01:51:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

/* iter() iterates throught the list tkns, by aplying to each of the element of
 * tkns the function f. */

static t_dlist	*iter(t_dlist **args, t_dlist *env_var, t_dlist *(*f)())
{
	t_arg	*arg;
	t_dlist	*elem;
	t_dlist	*next;

	elem = *args;
	while (elem)
	{
		next = elem->next;
		arg = (t_arg *) elem->content;
		elem = f(args, elem, arg, env_var);
		if (elem == NULL && next != NULL)
			return (NULL);
		else if (elem != next)
			elem = elem->next;
	}
	return (*args);
}

t_ast_tree_node	*apply_expansion_on_node(t_ast_tree_node *root, t_dlist *env_var)
{
	t_ast_tree_node	*cmd_node;
	t_dlist			*new_args;

	if (root->type == NODE_PIPE)
	{
		cmd_node = root->left;
		if (apply_expansion_on_node(root->right, env_var))
			return (NULL);
	}
	if (root->type == NODE_COMMAND)
		cmd_node = root;
	new_args = iter(&cmd_node->args, env_var, var_expansion);
	if (!new_args)
		return (NULL);
	cmd_node->args = new_args;
	new_args = iter(&cmd_node->args, env_var, wildcard_expansion);
	if (!new_args)
		return (NULL);
	cmd_node->args = new_args;
	return (root);
}
