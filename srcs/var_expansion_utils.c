/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:31:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/23 23:05:18 by plouvel          ###   ########.fr       */
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

static size_t	copy(t_token *tkn, char *old_str, char *new_str, t_var var)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	i_ret;
	t_list	*lst;

	i = 0;
	j = 0;
	k = 0;
	while (old_str[j] != '$')
		new_str[i++] = old_str[j++];
	if (var.value != NULL)
	{
		while (var.value[k] != '\0')
		{
			if (var.value[k] == SQUOTE || var.value[k] == DQUOTE)
			{
				lst = ft_lstnew((size_t *) malloc(sizeof(size_t)));
				* (size_t *)lst->content = i;
				ft_lstadd_back(&tkn->quote_list, lst);
			}
			new_str[i++] = var.value[k++];
		}
	}
	i_ret = i;
	j += 1 + var.name_len;
	while (old_str[j] != '\0')
		new_str[i++] = old_str[j++];
	new_str[i] = '\0';
	free(old_str);
	return (i_ret);
}

ssize_t	include_variable(t_token *tkn, char **str, t_var var)
{
	char	*new_str;
	size_t	str_len;
	ssize_t	i_ret;

	if (var.value != NULL)
		str_len = ft_strlen(*str) - (var.name_len + 1) + var.value_len;
	else
		str_len = ft_strlen(*str) - (var.name_len + 1);
	new_str = (char *) malloc((str_len + 1) * sizeof(char));
	if (!new_str)
		return (-1);
	i_ret = copy(tkn, *str, new_str, var);
	*str = new_str;
	return (i_ret);
}

bool	is_an_expanded_quote(t_list *quote_list, size_t i_quote)
{
	size_t	i;

	while (quote_list != NULL)
	{
		i = * (size_t *) quote_list->content;
		if (i == i_quote)
			return (true);
		quote_list = quote_list->next;
	}
	return (false);
}
