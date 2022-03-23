/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/23 14:19:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

t_token	*var_expansion(t_token *tkn, t_dlist *env_var)
{
	ssize_t	i;
	t_bool	can_expand;

	i = 0;
	can_expand = true;
	while (tkn->val[i] != '\0')
	{
		if (tkn->val[i] == SQUOTE)
		{
			if (can_expand)
				can_expand = false;
			else
				can_expand = true;
		}
		else if (can_expand && tkn->val[i] == '$')
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
