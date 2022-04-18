/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_mem_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 10:22:42 by plouvel          ###   ########.fr       */
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
	return (tkn);
}

void	free_token(void *tkn)
{
	t_token	*ptkn;

	ptkn = (t_token *) tkn;
	if (ptkn->type == T_WORD)
		free(ptkn->val);
	free(ptkn);
}
