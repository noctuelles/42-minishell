/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_post_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:46:48 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 15:58:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

/* expand_var_from_tkns() expand the potential correct variable in the tokens
 * array. It also remove quoting from the tokens.
 * lst_var is the double linked list containing all the shell variable.
 * Token that only contains a variable and this variable is incorrect are
 * assigned as a T_NULL token, and the token value is immediatly free . */

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
			if (lexer->tkns[i].len == 0)
			{
				free(lexer->tkns[i].val);
				lexer->tkns[i].type = T_NULL;
			}
		}
		i++;
	}
}
