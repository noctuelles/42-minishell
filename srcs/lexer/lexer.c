/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:47:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 10:22:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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

/* add_static_token() add the token tkn to the array of tokens.
 * In this function, tkn is a known token.
 * It also increment or decrement a counter that keep track of how many
 * parenthesis has been open / close. */

static int	add_static_token(t_lexer *lexer, t_token tkn, char **str)
{
	*str += tkn.len;
	if (tkn.type == T_OP_PRT)
		lexer->prt_cnt++;
	else if (tkn.type == T_CL_PRT)
		lexer->prt_cnt--;
	if (tkn.type != T_BREAK)
	{
		if (!add_to_tkns(&lexer->tkns, tkn.val, tkn.len, tkn.type))
			return (-1);
	}
	lexer->prev = *str;
	return (0);
}

/* finish_lexing ends the fill_lexer_from_str routine.
 * If a word is remaining at the end of the string str, it adds it to the lexer.
 * It also checks the parenthesis counter, if it's not 0, set the error code.*/

static int	finish_lexing(t_lexer *lexer, char *str)
{
	if (lexer->prev != str)
	{
		if (!add_to_tkns(&lexer->tkns, lexer->prev, str - lexer->prev, T_WORD))
			return (ERR_MEM);
	}
	if (lexer->prt_cnt != 0)
		return (ERR_PRT);
	if (!add_to_tkns(&lexer->tkns, NULL, 0, T_NULL))
		return (ERR_MEM);
	return (ERR_NO);
}

/* fill_lexer_from_str() fill the lexer from a string.
 * It breaks the string str into multiple tokens. */

static int	fill_lexer_from_str(t_lexer *lexer, char *str)
{
	t_token		tkn;

	while (*str)
	{
		tkn = search_existing_token(str);
		if ((tkn.type != T_NULL) && str != lexer->prev)
		{
			if (!add_to_tkns(&lexer->tkns, lexer->prev, str - lexer->prev,
					T_WORD))
				return (ERR_MEM);
		}
		if (tkn.type != T_NULL)
		{
			if (add_static_token(lexer, tkn, &str) == -1)
				return (ERR_MEM);
		}
		else if (*str == SQUOTE || *str == DQUOTE)
		{
			if (handle_escaping(&str) == -1)
				return (ERR_QUOTE);
		}
		else
			str++;
	}
	return (finish_lexing(lexer, str));
}

/* lex_str() returns a double linked list of tokens.
 * If any error occurs, the function displays and adequate error message. */

t_dlist	*lex_str(const char *str)
{
	t_token	*tkn;
	t_lexer	lexer;
	t_dlist	*last;
	int		ret;

	ft_memset(&lexer, 0, sizeof(lexer));
	lexer.prev = (char *) str;
	ret = fill_lexer_from_str(&lexer, (char *) str);
	if (ret != ERR_NO)
	{
		last = ft_dlstlast(lexer.tkns);
		if (last)
			tkn = (t_token *) last->content;
		if (ret == ERR_MEM)
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
		else if (last == NULL)
			ft_dprintf(STDERR_FILENO, STR_ERROR, get_lexer_error(ret));
		else
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR, get_lexer_error(ret),
				tkn->val);
		ft_dlstclear(&lexer.tkns, free_token);
	}
	return (lexer.tkns);
}
