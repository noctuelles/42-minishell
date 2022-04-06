/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:43:46 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/07 00:14:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

/* iter() iterates throught the list tkns, by aplying to each of the element of
 * tkns the function f. */

static t_dlist	*iter(t_dlist **tkns, t_dlist *env_var, t_dlist *(*f)())
{
	t_token	*tkn;
	t_dlist	*elem;

	elem = *tkns;
	while (elem)
	{
		tkn = (t_token *) elem->content;
		if (tkn->type == T_WORD)
		{
			elem = f(tkns, elem, tkn, env_var);
			if (elem == NULL)
				return (NULL);
		}
		elem = elem->next;
	}
	return (*tkns);
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
