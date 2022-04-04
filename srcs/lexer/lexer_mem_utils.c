/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_mem_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/04 16:46:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token	*new_token(char *val, size_t len, t_token_type type)
{
	t_token	*tkn;

	tkn = (t_token *) malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->val = val;
	tkn->len = len;
	tkn->type = type;
	tkn->wldc_list = NULL;
	tkn->quote_lst = NULL;
	tkn->quote = '\0';
	return (tkn);
}

void	free_token(void *tkn)
{
	t_token	*ptkn;
	
	ptkn = (t_token *) tkn;
	if (ptkn->type == T_WORD)
	{
		if (ptkn->wldc_list)
			ft_lstclear(&ptkn->wldc_list, NULL);
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
