/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:47:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 17:31:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* add_to_lexer() add to the lexer the lexicon define by three properties :
 *
 * -> It's value.
 * -> His lenght.
 * -> His type.
 *
 * The lexicon array (ref. as the tokens array) is dynamically allocated,
 * check the file lexer_memutils.c :
 *
 *      -> It has a base size of 2 tokens. It realloc the array if we're getting
 *      out of bound by a factor of 2.
 *      We're calling grow_tkns_array only if if we haven't allocated tkns,
 *      or if we're in the situation described below.
 *
 *      Arrays is better than linked list : in the parsing phase, looking at the
 *      next token or the previous token will be easier with array than with
 *      list, and faster. We sacrifice a bit of memory for convenience and
 *      speed.
 *
 * If the token a String (not an existing token), we're calling ft_strndup to
 * duplicate the token.
 *  */

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

/* handle_escaping() skip all character beetween the quote, thus avoiding
 * interpreting meta characters.
 * It returns -1 if the quote isn't finished, and 0 if the quote is 
 * successfully terminated.*/

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

/* add_token() add the token tkn to the array of tokens.
 * In this function, tkn is obviously a know token.
 * It also increment or decrement a counter that keep track of how many
 * parenthesis has been open / close. */

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

/* finish_lexing ends the fill_lexer_from_str routine.
 * If a word is remaining at the end of the string str, it adds it to the lexer.
 * It also checks the parenthesis counter, if it's not 0, set the error code. */

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

/* fill_lexer_from_str() fill the lexer from a string.
 * It breks the string str into multiple tokens. */

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
			if (handle_escaping(&str) == -1)
				return (set_lexer_errcode(lexer, E_QUOTE));
		}
		else
			str++;
	}
	return (finish_lexing(lexer, str));
}
