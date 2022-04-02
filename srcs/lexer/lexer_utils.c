/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:08:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/01 16:12:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

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

t_token	*add_to_lexer(t_lexer *lexer, char *val, size_t len,
															t_token_type type)
{
	char	*str;
	t_dlist	*elem;
	t_token	*tkn;

	str = val;
	if (type == T_WORD)
	{
		str = ft_strndup(val, len);
		if (!str)
			return (NULL);
	}
	tkn = new_token(str, len, type);
	if (!tkn)
	{
		free(str);
		return (NULL);
	}
	elem = ft_dlstnew((void *) tkn);
	if (!elem)
	{
		free_token(tkn);
		return (NULL);
	}
	ft_dlstadd_back(&lexer->tkns, elem);
	return (tkn);
}

t_token	set_token(t_token *tkn, char *val, size_t len,
														t_token_type type)
{
	tkn->val = val;
	tkn->len = len;
	tkn->type = type;
	tkn->wldc_list = NULL;
	tkn->quote = '\0';
	return (*tkn);
}

t_token	search_existing_token(const char *str)
{
	t_token	token;

	if (ft_strncmp(str, STR_LOG_OR, 2) == 0)
		return (set_token(&token, STR_LOG_OR, 2, T_LOG_OR));
	else if (ft_strncmp(str, STR_LOG_AND, 2) == 0)
		return (set_token(&token, STR_LOG_AND, 2, T_LOG_AND));
	else if (ft_strncmp(str, STR_RD_FILE_APN, 2) == 0)
		return (set_token(&token, STR_RD_FILE_APN, 2, T_DGRT));
	else if (ft_strncmp(str, STR_RD_STDIN_HEREDOC, 2) == 0)
		return (set_token(&token, STR_RD_STDIN_HEREDOC, 2, T_DLESS));
	else if (ft_strncmp(str, STR_PIPE, 1) == 0)
		return (set_token(&token, STR_PIPE, 1, T_PIPE));
	else if (ft_strncmp(str, STR_RD_FILE, 1) == 0)
		return (set_token(&token, STR_RD_FILE, 1, T_GRT));
	else if (ft_strncmp(str, STR_RD_STDIN, 1) == 0)
		return (set_token(&token, STR_RD_STDIN, 1, T_LESS));
	else if (ft_strncmp(str, STR_OP_PRT, 1) == 0)
		return (set_token(&token, STR_OP_PRT, 1, T_OP_PRT));
	else if (ft_strncmp(str, STR_CL_PRT, 1) == 0)
		return (set_token(&token, STR_CL_PRT, 1, T_CL_PRT));
	else if (ft_strncmp(str, STR_SP, 1) == 0)
		return (set_token(&token, STR_SP, 1, T_BREAK));
	return (set_token(&token, NULL, 0, T_NULL));
}

bool	is_a_intrp_wldc(t_list *wldc_list, char *c)
{
	while (wldc_list != NULL)
	{
		if ((char *) wldc_list->content == c)
			return (true);
		wldc_list = wldc_list->next;
	}
	return (false);
}
