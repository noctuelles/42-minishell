/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:31:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/29 17:45:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

// get_var_value will return the value if any.

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

static ssize_t	copy_var(t_token *tkn, char *new_str, t_var var, size_t i)
{
	size_t	k;
	t_list	*elem;

	k = 0;
	if (!tkn->quote)
	{
		while (var.value[k] == ' ')
			k++;
	}
	while (var.value[k] != '\0')
	{
		if (var.value[k] == '*' && !tkn->quote)
		{
			elem = ft_lstnew((char *) &new_str[i]);
			if (!elem)
				return (-1);
			ft_lstadd_back(&tkn->wldc_list, elem);
		}
		new_str[i++] = var.value[k++];
	}
	return (i);
}

static ssize_t	copy(t_token *tkn, char *new_str, t_var var)
{
	ssize_t	i;
	size_t	j;
	size_t	i_ret;

	i = 0;
	j = 0;
	while (tkn->val[j] != '$')
		new_str[i++] = tkn->val[j++];
	if (var.value != NULL)
	{
		i = copy_var(tkn, new_str, var, i);
		if (i == -1)
			return (-1);
	}
	i_ret = i;
	j += 1 + var.name_len;
	while (tkn->val[j] != '\0')
		new_str[i++] = tkn->val[j++];
	new_str[i] = '\0';
	free(tkn->val);
	return (i_ret);
}

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
		return (-1);
	i_ret = copy(tkn, new_str, var);
	if (i_ret == -1)
		free(new_str);
	else
		tkn->val = new_str;
	return (i_ret);
}

bool	is_a_intrp_wildcard(t_list *wldc_list, char *c)
{
	while (wldc_list != NULL)
	{
		if ((char *) wldc_list->content == c)
			return (true);
		wldc_list = wldc_list->next;
	}
	return (false);
}
