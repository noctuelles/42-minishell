/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:43:46 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/15 16:26:25 by plouvel          ###   ########.fr       */
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
		if (elem != next)
			elem = elem->next;
		else if (elem == NULL && next != NULL)
			return (NULL);
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
		apply_expansion_on_node(root->right, env_var);
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
	return (root);
}

/* clean() exit the get_tokens() function by displaying an error message and
 * freeing all ressources. */

static t_dlist	*clean(t_dlist **tkns)
{
	ft_dprintf(STDERR_FILENO, STR_ERROR, strerror(errno));
	ft_dlstclear(tkns, free_token);
	return (NULL);
}

/* get_tokens() first get a token list from lex_str, then the variable expansion
 * and the filename expansion.
 * If any of these expansion fails, the function return NULL. */

t_dlist	*get_tokens(char *str, t_dlist *env_var)
{
	t_dlist	*tkns;
	t_dlist	*new_tkns;

	tkns = lex_str(str);
	if (!tkns)
		return (NULL);
	new_tkns = iter(&tkns, env_var, var_expansion);
	if (!new_tkns)
		return (clean(&tkns));
	tkns = new_tkns;
	new_tkns = iter(&new_tkns, NULL, wildcard_expansion);
	if (!new_tkns)
		return (clean(&tkns));
	return (new_tkns);
}
