/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:20:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/05 14:31:33 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static inline t_list	*add_to_list(t_list **list, void *content)
{
	t_list	*elem;

	elem = ft_lstnew(content);
	if (!elem)
		return (NULL);
	ft_lstadd_back(list, elem);
	return (elem);
}

static inline void	check_for_break(t_lexer *lex)
{
	if (*lex->str == ' ')
		lex->bbreak = true;
	else
		lex->bbreak = false;
}

static inline t_list	*handle_escaping(t_token *tkn, char **str)
{
	char	*pstr;
	char	quote;
	pstr = *str;
	if (add_to_list(&tkn->rem_quote_lst, pstr) == NULL)
		return (NULL);
	quote = *pstr++;
	while (*pstr)
	{
		if (*pstr == quote && !is_expnd_quote(tkn->quote_lst, pstr))
			break ;
		pstr++;
	}
	if (add_to_list(&tkn->rem_quote_lst, pstr) == NULL)
		return (NULL);
	pstr++;
	*str = pstr;
	return (tkn->rem_quote_lst);
}

static t_dlist	*clean(t_dlist **list)
{
	ft_dlstclear(list, free_token);
	return (NULL);
}

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

static char	*ft_strndup_wldc(t_token *old_tkn, const char *s, size_t n)
{
	char	*str;

	if (!s || n == 0)
		return (NULL);
	str = (char *) malloc((n - ft_lstsize(old_tkn->rem_quote_lst) + 1)
			* sizeof(char));
	copy(old_tkn, s, str, n);
	return (str);
}

static t_token	*add_to_tkns_cpy(t_lexer *lex, t_token *old_tkn)
{
	char	*str;
	t_dlist	*elem;
	t_token	*tkn;

	str = ft_strndup_wldc(old_tkn, lex->prev, lex->str - lex->prev);
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

static void	update_prev(char **str, char **prev)
{
	*str += 1;
	*prev = *str;
}

static t_dlist	*finish_tokenizing(t_lexer *lex, t_token *old_tkn)
{
	if (lex->prev != lex->str)
	{
		if (add_to_tkns_cpy(lex, old_tkn) == NULL)
			return (NULL);
	}
	return (lex->tkns);
}

static t_token	*handle_new_token(t_lexer *lex, t_token *old_tkn)
{
	t_token	*tkn;

	tkn = old_tkn;
	if (lex->bbreak && lex->str != lex->prev)
	{
		tkn = add_to_tkns_cpy(lex, old_tkn);
		if (tkn == NULL)
			return (NULL);
	}
	else if (*lex->str == '*')
	{
		if (add_to_list(&old_tkn->wldc_lst, lex->str) == NULL)
			return (NULL);
	}
	return (tkn);
}

t_dlist	*re_tokenize(t_token *old_tkn, char *str)
{
	t_lexer	lex;

	lex.str = str;
	lex.bbreak = false;
	lex.prev = str;
	lex.tkns = NULL;
	while (*lex.str)
	{
		check_for_break(&lex);
		if (handle_new_token(&lex, old_tkn) == NULL)
			return (clean(&lex.tkns));
		if (lex.bbreak)
			update_prev(&lex.str, &lex.prev);
		else if ((*lex.str == SQUOTE || *lex.str == DQUOTE)
				&& !is_expnd_quote(old_tkn->quote_lst, lex.str))
		{
			if (handle_escaping(old_tkn, &lex.str) == NULL)
				return (clean(&lex.tkns));
		}
		else
			lex.str++;
	}
	return (finish_tokenizing(&lex, old_tkn));
}
