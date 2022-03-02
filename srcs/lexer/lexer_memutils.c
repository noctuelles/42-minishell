/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 18:59:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	free_tkns(t_token *tkns, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (tkns[i].type == T_WORD)
			free(tkns[i].val);
		i++;
	}
	free(tkns);
}

t_token	*grow_tkns_array(t_lexer *lexer)
{
	size_t	new_size;
	t_token	*old_tkns;

	old_tkns = lexer->tkns;
	if (lexer->size != 0)
		new_size = lexer->size * 2;
	else
		new_size = 2;
	lexer->tkns = ft_realloc(old_tkns, lexer->size * sizeof(t_token),
			new_size * sizeof(t_token));
	if (!lexer->tkns)
	{
		free_tkns(old_tkns, lexer->idx);
		return (NULL);
	}
	free(old_tkns);
	lexer->size = new_size;
	return (lexer->tkns);
}
