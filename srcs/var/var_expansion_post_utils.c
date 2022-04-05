/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:35:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/05 14:44:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	copy(t_token *old_tkn, const char *s, char *str, size_t n)
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
			elem = is_intrp_wldc(old_tkn->wldc_lst, (char *) &s[i]);
			if (elem)
				elem->content = &str[j];
		}
		if ((s[i] == SQUOTE || s[i] == DQUOTE)
				&& is_rem_quote(old_tkn->rem_quote_lst, (char *) &s[i]))
				i++;
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
}

static char	*ft_strndup_tkn(t_token *old_tkn, const char *s, size_t n)
{
	char	*str;

	if (!s || n == 0)
		return (NULL);
	str = (char *) malloc((n - ft_lstsize(old_tkn->rem_quote_lst) + 1)
			* sizeof(char));
	copy(old_tkn, s, str, n);
	return (str);
}

t_token	*add_to_tkns_cpy(t_lexer *lex, t_token *old_tkn)
{
	char	*str;
	t_dlist	*elem;
	t_token	*tkn;

	str = ft_strndup_tkn(old_tkn, lex->prev, lex->str - lex->prev);
	if (!str)
		return (NULL);
	tkn = new_token(str, lex->str - lex->prev, T_WORD);
	if (!tkn)
	{
		free(str);
		return (NULL);
	}
	tkn->wldc_lst = old_tkn->wldc_lst;
	old_tkn->wldc_lst = NULL;
	elem = ft_dlstnew((void *) tkn);
	if (!elem)
	{
		free_token(tkn);
		return (NULL);
	}
	ft_dlstadd_back(&lex->tkns, elem);
	return (tkn);
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
