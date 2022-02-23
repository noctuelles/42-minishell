/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:47:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/23 12:43:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*add_to_lexer(t_lexer *lexer, char *val, size_t len,
															t_token_type type)
{
	char	*str;

	if (lexer->size == 0 || lexer->idx == lexer->size)
	{
		lexer->tkns = grow_tkns_array(lexer);
		if (!lexer->tkns)
			return (NULL);
	}
	if (type == T_STRING)
	{
		str = ft_strndup(val, len);
		if (!str)
		{
			free_tkns(lexer->tkns, lexer->idx);
			return (NULL);
		}
	}
	else
		str = val;
	set_token(&lexer->tkns[lexer->idx], str, len, type);
	lexer->idx++;
	return (lexer->tkns);
}

static int	handle_escaping(char **str)
{
	char	*pstr;
	char	quote;

	pstr = *str;
	quote = *pstr++;
	while (*pstr && *pstr != quote)
		pstr++;
	if (!*pstr)
		return (-1);
	pstr++;
	*str = pstr;
	return (0);
}

static int	add_token(t_lexer *lexer, t_token tkn, char **str)
{
	*str += tkn.len;
	if (tkn.type == T_OP_PRT)
		lexer->prt_cnt++;
	else if (tkn.type == T_CL_PRT)
		lexer->prt_cnt--;
	if (tkn.type != T_BREAK)
	{
		if (!add_to_lexer(lexer, tkn.val, tkn.len, tkn.type))
			return (-1);
	}
	lexer->prev = *str;
	return (0);
}

static t_lexer	*finish_lexing(t_lexer *lexer, char *str)
{
	if (lexer->prev != str)
	{
		if (!add_to_lexer(lexer, lexer->prev, str - lexer->prev, T_STRING))
			return (set_lexer_errcode(lexer, E_MEM));
	}
	if (lexer->prt_cnt != 0)
		return (set_lexer_errcode(lexer, E_PRT));
	return (lexer);
}

t_lexer	*fill_lexer_from_str(t_lexer *lexer, char *str)
{
	t_token		tkn;

	lexer->prev = str;
	while (*str)
	{
		tkn = search_existing_token(str);
		if ((tkn.type != T_NULL) && str != lexer->prev)
		{
			if (!add_to_lexer(lexer, lexer->prev, str - lexer->prev, T_STRING))
				return (set_lexer_errcode(lexer, E_MEM));
		}
		if (tkn.type != T_NULL)
		{
			if (add_token(lexer, tkn, &str) == -1)
				return (set_lexer_errcode(lexer, E_MEM));
		}
		else if (*str == SQUOTE || *str == DQUOTE)
		{
			if (handle_escaping(lexer, &str) == -1)
				return (set_lexer_errcode(lexer, E_QUOTE));
		}
		else
			str++;
	}
	return (finish_lexing(lexer, str));
}
