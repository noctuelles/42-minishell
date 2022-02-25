/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_post_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:46:48 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 19:47:39 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

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

void	expand_var_from_tkns(t_dlist *lst_var, t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->idx)
	{
		if (lexer->tkns[i].type == T_STRING)
		{
			lexer->tkns[i].val = expand_tkn(lst_var, lexer->tkns[i].val);
			lexer->tkns[i].len = ft_strlen(lexer->tkns[i].val);
		}
		i++;
	}
}
