/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:20:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/05 04:25:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static inline t_list	*add_list(t_list **list, void *content)
{
	t_list	*elem;

	elem = ft_lstnew(content);
	if (!elem)
		return (NULL);
	ft_lstadd_back(list, elem);
	return (elem);
}

static inline void	check_for_break(char c, bool *space)
{
	if (c == ' ')
		*space = true;
	else
		*space = false;
}

static inline void	handle_escaping(t_token *tkn, char **str)
{
	char	*pstr;
	char	quote;
	pstr = *str;
	add_list(&tkn->rem_quote_lst, pstr);
	quote = *pstr++;
	while (*pstr)
	{
		if (*pstr == quote && is_intrp_quote(tkn->quote_lst, pstr))
			break ;
		pstr++;
	}
	add_list(&tkn->rem_quote_lst, pstr);
	pstr++;
	*str = pstr;
}

static t_dlist	*clean(t_dlist **list, t_list **wldc_list)
{
	ft_dlstclear(list, free_token);
	if (wldc_list)
		ft_lstclear(wldc_list, NULL);
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
				&& !is_intrp_quote(old_tkn->rem_quote_lst, (char *) &s[i]))
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

static t_token	*add_to_tkns_wldc(t_dlist **tkns, t_token *old_tkn,
														char *val, size_t len)
{
	char	*str;
	t_dlist	*elem;
	t_token	*tkn;

	str = ft_strndup_wldc(old_tkn, val, len);
	if (!str)
		return (NULL);
	tkn = new_token(str, len, T_WORD);
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
	ft_dlstadd_back(tkns, elem);
	return (tkn);
}

static t_list	*add_wldc_addr(t_list **wldc_lst, char *psaddr)
{
	t_list	*elem;

	elem = ft_lstnew((void *) psaddr);
	if (!elem)
		return (NULL);
	elem->content = psaddr;
	ft_lstadd_back(wldc_lst, elem);
	return (elem);
}

t_dlist	*re_tokenize(t_token *old_tkn, char *str)
{
	bool	bbreak;
	char	*prev;
	t_dlist	*list;

	bbreak = false;
	prev = str;
	list = NULL;
	while (*str)
	{
		check_for_break(*str, &bbreak);
		if (bbreak && str != prev)
		{
			if (add_to_tkns_wldc(&list, old_tkn, prev, str - prev) == NULL)
				return (NULL);
		}
		else if (*str == '*')
		{
			if (add_wldc_addr(&old_tkn->wldc_lst, str) == NULL)
				return (NULL);
		}
		if (bbreak)
		{
			str += 1;
			prev = str;
		}
		else if ((*str == SQUOTE || *str == DQUOTE) && is_intrp_quote(old_tkn->quote_lst, str))
		{
			handle_escaping(old_tkn, &str);
		}
		else
			str++;
	}
	if (prev != str)
	{
		if (add_to_tkns_wldc(&list, old_tkn, prev, str - prev) == NULL)
			return (NULL);
	}
	return (list);
}
