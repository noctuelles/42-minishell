/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/22 22:15:39 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

/* get_var_name_len() computes the lenght of a variable .
 * Variable in bash can only contains alphanumerical characters, and an
 * unlimited amount of underscore '_'. */

static size_t	get_var_name_len(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

static size_t	perform_expansion_cpy(char *new_str, char *str, t_var *var,
															size_t var_name_len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	idx_ret;

	i = 0;
	j = 0;
	k = 0;
	while (str[j] != '$')
		new_str[i++] = str[j++];
	j++;
	if (var)
	{
		while (var->value[k] != '\0')
			new_str[i++] = var->value[k++];
	}
	idx_ret = i - 1;
	j += var_name_len;
	while (str[j] != '\0')
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	free(str);
	return (idx_ret);
}

static char	*include_var(char *str, t_var *var, size_t var_name_len,
																size_t *idx)
{
	char	*new_str;
	size_t	str_len;

	if (var)
		str_len = (ft_strlen(str) - (var_name_len + 1)) + var->value_len;
	else
		str_len = ft_strlen(str) - (var_name_len + 1);
	new_str = (char *) malloc((str_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	*idx = perform_expansion_cpy(new_str, str, var, var_name_len);
	return (new_str);
}

static char	*perform_expansion(t_dlist *lst_var, char *str, size_t *i)
{
	t_var	*var;
	char	ctemp;
	size_t	var_name_len;

	(*i)++;
	var_name_len = get_var_name_len(&str[*i]);
	ctemp = str[*i + var_name_len];
	str[*i + var_name_len] = '\0';
	var = get_var(lst_var, &str[*i]);
	str[*i + var_name_len] = ctemp;
	return (include_var(str, var, var_name_len, i));
}

/*
 *
 */

char	*var_expansion(char *str, t_dlist *env_var)
{
	size_t	i;
	t_var	var;
	t_bool	can_expand;

	i = 0;
	can_expand = true;
	while (str[i] != '\0')
	{
		if (str[i] == SQUOTE)
		{
			if (can_expand)
				can_expand = false;
			else
				can_expand = true;
		}
		else if (can_expand && str[i] == '$')
		{
			var = dump_var_info(&str[i + 1], env_var);
			i = alloc(&str, var);
			if (i == -1)
				return (NULL);
		}
	}
}
