/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 19:47:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <assert.h>

static size_t	get_var_name_len(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

static size_t	perform_expansion_cpy(char *new_str, char *str, t_var *var,
																size_t var_len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	idx_ret;

	i = 0;
	j = 0;
	k = 0;
	while (str[j] != '$')
	{
		puts("ok");
		new_str[i++] = str[j++];
	}
	j++;
	if (var)
	{
		while (var->value[k] != '\0')
			new_str[i++] = var->value[k++];
	}
	idx_ret = i - 1;
	j += var_len;
	while (str[j] != '\0')
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	free(str);
	return (idx_ret);
}

static char	*include_var(char *str, t_var *var, size_t var_len, size_t *idx)
{
	char	*new_str;
	size_t	str_len;

	if (var)
		str_len = (ft_strlen(str) - (var_len + 1)) + var->value_len;
	else
		str_len = ft_strlen(str) - (var_len + 1);
	new_str = (char *) malloc((str_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	*idx = perform_expansion_cpy(new_str, str, var, var_len);
	//printf("New string : %s\nReturning to : \"%c\"\n", new_str, new_str[*idx]);
	return (new_str);
}

static char	*perform_expansion(t_dlist *lst_var, char *str, size_t *i)
{
	t_var	*var;
	char	ctemp;
	size_t	var_len;

	//puts("New dollar sign.");
	(*i)++;
	var_len = get_var_name_len(&str[*i]);
	ctemp = str[*i + var_len];
	str[*i + var_len] = '\0';
	var = get_var(lst_var, &str[*i]);
	str[*i + var_len] = ctemp;
	return (include_var(str, var, var_len, i));
}

char	*expand_tkn(t_dlist *lst_var, char *str)
{
	size_t	i;
	t_bool	can_expand;

	i = 0;
	can_expand = TRUE;
	while (str[i] != '\0')
	{
		if (str[i] == SQUOTE)
		{
			if (can_expand)
				can_expand = FALSE;
			else
				can_expand = TRUE;
		}
		else if (str[i] == '$' && can_expand)
		{
			str = perform_expansion(lst_var, str, &i);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
