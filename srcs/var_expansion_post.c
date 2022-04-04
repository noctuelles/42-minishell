/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:20:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/04 16:56:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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
	quote = *pstr;
	ft_strdelchr(pstr++);
	while (*pstr)
	{
		if (*pstr == quote && is_intrp_quote(tkn->quote_lst, pstr))
			break ;
		pstr++;
	}
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

t_dlist	*re_tokenize(t_token *tkn, char *str)
{
	bool	bbreak;
	char	*prev;
	t_dlist	*list;
	t_list	*elem;

	bbreak = false;
	prev = str;
	list = NULL;
	while (*str)
	{
		check_for_break(*str, &bbreak);
		if (bbreak && str != prev)
			add_to_tkns(&list, prev, str - prev, T_WORD);
		if (bbreak)
		{
			str += 1;
			prev = str;
		}
		else if (*str == '*')
		{
		}
		else if (*str == SQUOTE || *str == DQUOTE)
			handle_escaping(tkn, &str);
		else
			str++;
	}
	if (prev != str)
		add_to_tkns(&list, prev, str - prev, T_WORD);
	return (list);
}
