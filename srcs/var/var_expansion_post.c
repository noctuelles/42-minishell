/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_post.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:20:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 12:21:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_list	*handle_escaping(t_arg *arg, char **str)
{
	char	*pstr;
	char	quote;

	pstr = *str;
	if (add_to_list(&arg->rem_quote_lst, pstr) == NULL)
		return (NULL);
	quote = *pstr++;
	while (*pstr)
	{
		if (*pstr == quote && !is_expnd_quote(arg->quote_lst, pstr))
			break ;
		pstr++;
	}
	if (add_to_list(&arg->rem_quote_lst, pstr) == NULL)
		return (NULL);
	pstr++;
	*str = pstr;
	return (arg->rem_quote_lst);
}

static inline t_dlist	*clean(t_dlist **list)
{
	ft_dlstclear(list, free_arg);
	return (NULL);
}

static inline t_dlist	*finish_tokenizing(t_lexer *lex, t_arg *old_arg)
{
	if (lex->prev != lex->str)
	{
		if (add_to_args_cpy(lex, old_arg) == NULL)
			return (NULL);
	}
	return (lex->tkns);
}

static t_arg	*handle_new_token(t_lexer *lex, t_arg *old_arg)
{
	t_arg	*arg;

	arg = old_arg;
	if (lex->bbreak && lex->str != lex->prev)
	{
		arg = add_to_args_cpy(lex, old_arg);
		if (!arg)
			return (NULL);
	}
	else if (*lex->str == '*')
	{
		if (!add_to_list(&old_arg->wldc_lst, lex->str))
			return (NULL);
	}
	return (arg);
}

t_dlist	*tokenize_from_arg(t_arg *old_arg, char *str)
{
	t_lexer	lex;

	lex.str = str;
	lex.bbreak = false;
	lex.prev = str;
	lex.tkns = NULL;
	while (*lex.str)
	{
		check_for_break(&lex);
		if (handle_new_token(&lex, old_arg) == NULL)
			return (clean(&lex.tkns));
		if (lex.bbreak)
			update_prev(&lex);
		else if ((*lex.str == SQUOTE || *lex.str == DQUOTE)
			&& !is_expnd_quote(old_arg->quote_lst, lex.str))
		{
			if (handle_escaping(old_arg, &lex.str) == NULL)
				return (clean(&lex.tkns));
		}
		else
			lex.str++;
	}
	return (finish_tokenizing(&lex, old_arg));
}
