/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:47:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/22 20:13:24 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

static t_token	*new_token(char *val, size_t len, t_token_type type)
{
	t_token	*tkn;
	char	*str;

	tkn = (t_token *) malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	if (type == T_STRING)
	{
		str = ft_strndup((const char *) val, len);
		if (!str)
		{
			free(tkn);
			return (NULL);
		}
	}
	else
		str = val;
	set_token(tkn, str, len, type);
	return (tkn);
}

static t_list	*add_to_lexer(t_lexer *lexer, char *val, size_t len,
															t_token_type type)
{
	t_list	*elem;
	t_token	*tkn;

	tkn = new_token(val, len, type);
	if (!tkn)
		return (NULL);
	elem = ft_lstnew((void *) tkn);
	if (!elem)
	{
		if (type == T_STRING)
			free(tkn->val);
		free(tkn);
		return (NULL);
	}
	ft_lstadd_back(&lexer->tkn_lst, elem);
	return (lexer->tkn_lst);
}

t_lexer	*fill_lexer_from_str(t_lexer *lexer, char *str)
{
	char		*prev;
	t_token		tkn;
	uint32_t	prt_cnt;
	char		quote;

	prev = str;
	prt_cnt = 0;
	while (*str)
	{
		tkn = search_existing_token(str);
		if ((tkn.type != T_NULL) && str != prev)
		{
			if (!add_to_lexer(lexer, prev, str - prev, T_STRING))
				return (NULL);
			if (*str == '\'' || *str == '\"')
				prev = str;
		}
		if (tkn.type != T_NULL)
		{
			str += tkn.len;
			if (tkn.type != T_BREAK)
			{
				if (!add_to_lexer(lexer, tkn.val, tkn.len, tkn.type))
					return (NULL);
			}
			prev = str;
		}
		else if (*str == '\'' || *str == '"')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (!*str || *str != quote)
				return (NULL);
			str++;
		}
		else
			str++;
	}
	if (prev != str)
	{
		if (!add_to_lexer(lexer, prev, str - prev, T_STRING))
			return (NULL);
	}
	return (lexer);
}
