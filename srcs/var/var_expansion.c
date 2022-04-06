/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/06 13:53:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static void	update_quote(char *str, char *quote)
{
	if (*quote == '\0')
		*quote = *str;
	else if (*str == *quote)
		*quote = '\0';
}

static t_dlist	*post_process(t_dlist **tkns, t_dlist *elem, t_token *tkn)
{
	t_dlist	*next;
	t_dlist	*subtkns;

	if (tkn->val[0] == '\0')
	{
		next = elem->next;
		ft_dlstdelone(tkns, elem, free_token);
		return (next);
	}
	else
	{
		subtkns = tokenize_from_tkn(tkn, tkn->val);
		if (subtkns == NULL)
			return (NULL);
		return (insert_list(tkns, subtkns, elem));
	}
}

t_dlist	*var_expansion(t_dlist **tkns, t_dlist *elem,
		t_token *tkn, t_dlist *env_var)
{
	ssize_t	i;
	t_dlist	*subtkns;

	i = 0;
	while (tkn->val[i] != '\0')
	{
		if (tkn->val[i] == SQUOTE || tkn->val[i] == DQUOTE)
			update_quote(&tkn->val[i], &tkn->quote);
		else if (tkn->quote != SQUOTE && tkn->val[i] == '$')
		{
			i = include_variable(tkn, get_var_info(&tkn->val[i + 1], env_var));
			if (i == -2)
				return (NULL);
		}
		i++;
	}
	subtkns = post_process(tkns, elem, tkn);
	if (subtkns == NULL)
		return (NULL);
	else
		return (subtkns);
}
