/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:35:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/16 17:07:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	copy(t_arg *old_arg, const char *s, char *str, size_t n)
{
	t_list	*elem;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && i < n)
	{
		if (s[i] == '*')
		{
			elem = is_intrp_wldc(old_arg->wldc_lst, (char *) &s[i]);
			if (elem)
				elem->content = &str[j];
		}
		if ((s[i] == SQUOTE || s[i] == DQUOTE)
			&& is_rem_quote(old_arg->rem_quote_lst, (char *) &s[i]))
				i++;
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
}

static char	*ft_strndup_arg(t_arg *old_arg, const char *s, size_t n)
{
	char	*str;

	if (!s || n == 0)
		return (NULL);
	str = (char *) malloc((n - ft_lstsize(old_arg->rem_quote_lst) + 1)
			* sizeof(char));
	if (!str)
		return (NULL);
	copy(old_arg, s, str, n);
	return (str);
}

t_arg	*add_to_args_cpy(t_lexer *lex, t_arg *old_arg)
{
	char	*str;
	t_dlist	*elem;
	t_arg	*arg;

	str = ft_strndup_arg(old_arg, lex->prev, lex->str - lex->prev);
	if (!str)
		return (NULL);
	arg = new_arg(str, T_WORD, false);
	arg->type = old_arg->type;
	if (!arg)
	{
		free(str);
		return (NULL);
	}
	arg->wldc_lst = old_arg->wldc_lst;
	old_arg->wldc_lst = NULL;
	elem = ft_dlstnew((void *) arg);
	if (!elem)
	{
		free_arg(arg);
		return (NULL);
	}
	ft_dlstadd_back(&lex->tkns, elem);
	return (arg);
}

void	check_for_break(t_lexer *lex)
{
	if (*lex->str == ' ')
		lex->bbreak = true;
	else
		lex->bbreak = false;
}

void	update_prev(t_lexer *lex)
{
	lex->str += 1;
	lex->prev = lex->str;
}
