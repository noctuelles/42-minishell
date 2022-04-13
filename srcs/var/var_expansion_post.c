/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:04:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 10:04:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_list	*handle_escaping(t_token *tkn, char **str)
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

static inline t_dlist	*clean(t_dlist **list)
{
	ft_dlstclear(list, free_token);
	return (NULL);
}

static inline t_dlist	*finish_tokenizing(t_lexer *lex, t_token *old_tkn)
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

t_dlist	*tokenize_from_tkn(t_token *old_tkn, char *str)
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
			update_prev(&lex);
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
