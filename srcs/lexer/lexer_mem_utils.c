/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_mem_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/13 13:50:44 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(char *val, size_t len, t_token_type type)
{
	t_token	*tkn;

	tkn = (t_token *) malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->val = val;
	tkn->len = len;
	tkn->type = type;
	tkn->wldc_lst = NULL;
	tkn->quote_lst = NULL;
	tkn->rem_quote_lst = NULL;
	tkn->quote = '\0';
	return (tkn);
}

void	free_token(void *tkn)
{
	t_token	*ptkn;

	ptkn = (t_token *) tkn;
	if (ptkn->type == T_WORD)
	{
		if (ptkn->wldc_lst)
			ft_lstclear(&ptkn->wldc_lst, NULL);
		if (ptkn->quote_lst)
			ft_lstclear(&ptkn->quote_lst, NULL);
		if (ptkn->rem_quote_lst)
			ft_lstclear(&ptkn->rem_quote_lst, NULL);
		free(ptkn->val);
	}
	free(ptkn);
}

t_lexer	*new_lexer(void)
{
	t_lexer	*lexer;

	lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	return (lexer);
}

void	free_lexer(t_lexer *lexer)
{
	ft_dlstclear(&lexer->tkns, free_token);
	free(lexer);
}
