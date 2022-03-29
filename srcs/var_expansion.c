/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/28 18:41:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static void update_quote(char *str, char *quote)
{
	if (!*quote)
	{
		*quote = *str;
		ft_strdelchr(str);
	}
	else if (*str == *quote)
	{
		*quote = '\0';
		ft_strdelchr(str);
	}
}

t_token	*var_expansion(t_token *tkn, t_dlist *env_var)
{
	ssize_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (tkn->val[i] != '\0')
	{
		if (tkn->val[i] == SQUOTE || tkn->val[i] == DQUOTE)
			update_quote(&tkn->val[i], &quote);
		if (!quote && tkn->val[i] == '*')
			ft_lstadd_back(&tkn->wldc_list, ft_lstnew((char *) &tkn->val[i]));
		if (quote != SQUOTE && tkn->val[i] == '$')
		{
			i = include_variable(tkn, &tkn->val, get_var_info(
						&tkn->val[i + 1], env_var));
			if (i == -1)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (tkn);
}
