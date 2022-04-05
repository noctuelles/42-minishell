/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/05 03:23:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static void update_quote(char *str, char *quote)
{
	if (*quote == '\0')
		*quote = *str;
	else if (*str == *quote)
		*quote = '\0';
}

t_dlist	*re_tokenize(t_token *old_tkn, char *str);

/*
 *	If include_variable fails, the lexer entire lexer should be free.
 */

t_token	*var_expansion(t_token *tkn, t_dlist *env_var)
{
	ssize_t	i;

	i = 0;
	while (tkn->val[i] != '\0')
	{
		if (tkn->val[i] == SQUOTE || tkn->val[i] == DQUOTE)
			update_quote(&tkn->val[i], &tkn->quote);
		else if (tkn->quote != SQUOTE && tkn->val[i] == '$')
		{
			i = include_variable(tkn, get_var_info(&tkn->val[i + 1], env_var));
			if (i == -1)
				return (NULL);
		}
		i++;
	}
	t_dlist	*test = re_tokenize(tkn, tkn->val);
	ft_dlstiter(test, print_tokens);
	return (tkn);
}
