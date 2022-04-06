/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:31:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/06 14:41:56 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/* get_var_info() will read the variable name and return informations if
 * the variable exist in the double linked list env_var. */

t_var	get_var_info(char *str, t_dlist *env_var)
{
	t_var	*var;
	t_var	default_var;
	size_t	i;
	char	temp;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	temp = str[i];
	str[i] = '\0';
	var = get_var(env_var, str);
	str[i] = temp;
	if (var)
		return (*var);
	else
	{
		default_var.name_len = i;
		default_var.value = NULL;
		return (default_var);
	}
}

/* copy_var() copy the variable var into the new string.
 * If double quote or simple quote are detected, they're flagged using a linked
 * list. */

static ssize_t	copy_var(t_list **quote_lst, char *new_str, t_var var, size_t i)
{
	size_t	k;
	t_list	*elem;

	k = 0;
	while (var.value[k] != '\0')
	{
		if (var.value[k] == SQUOTE || var.value[k] == DQUOTE)
		{
			elem = add_to_list(quote_lst, (void *) &new_str[i]);
			if (!elem)
				return (-2);
		}
		new_str[i++] = var.value[k++];
	}
	return (i);
}

/* copy() perform the copy of the old token value, and include if exist, the
 * environnement variable var. */

static ssize_t	copy(t_token *tkn, char *new_str, t_var var)
{
	ssize_t	i;
	size_t	j;
	ssize_t	i_ret;

	i = 0;
	j = 0;
	while (tkn->val[j] != '$')
		new_str[i++] = tkn->val[j++];
	if (var.value != NULL)
	{
		i = copy_var(&tkn->quote_lst, new_str, var, i);
		if (i == -2)
			return (-2);
	}
	i_ret = i - 1;
	j += 1 + var.name_len;
	while (tkn->val[j] != '\0')
		new_str[i++] = tkn->val[j++];
	new_str[i] = '\0';
	free(tkn->val);
	return (i_ret);
}

/* include_variable() re-alloc a new string and perform a copy of the env
 * variable into the content of the old token. */

ssize_t	include_variable(t_token *tkn, t_var var)
{
	char	*new_str;
	size_t	str_len;
	ssize_t	i_ret;

	if (var.value != NULL)
		str_len = ft_strlen(tkn->val) - (var.name_len + 1) + var.value_len;
	else
		str_len = ft_strlen(tkn->val) - (var.name_len + 1);
	new_str = (char *) malloc((str_len + 1) * sizeof(char));
	if (!new_str)
		return (-2);
	i_ret = copy(tkn, new_str, var);
	if (i_ret == -2)
		free(new_str);
	else
		tkn->val = new_str;
	return (i_ret);
}
