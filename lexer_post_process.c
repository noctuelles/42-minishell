/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_post_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:46:48 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/23 12:51:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	remove_quote_from_tkns(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->idx)
	{
		if (lexer->tkns[i].type == T_STRING)
			lexer->tkns[i].val = ft_strdelchr(lexer->tkns[i].val, "\"'");
		i++;
	}
}

void	expand_var_from_tkns(t_lexer *lexer)
{
	(void) lexer;
}
