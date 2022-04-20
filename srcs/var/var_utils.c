/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:00:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 16:08:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_dprintf.h"
#include <stdlib.h> 

t_var	*update_var(t_dlist *lst_var, char *name, t_var to_update)
{
	t_var		*var;

	while (lst_var)
	{
		var = (t_var *) lst_var->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			*var = to_update;
			return (var);
		}
		lst_var = lst_var->next;
	}
	return (NULL);
}

/* get_var() returns a pointer to a shell variable, searching by it's name.
 * If the variable doesn't exist, the function return NULL. */

t_var	*get_var(t_dlist *lst_var, char *name)
{
	t_var	*var;

	while (lst_var)
	{
		var = (t_var *) lst_var->content;
		if (ft_strcmp(var->name, name) == 0)
			return (var);
		lst_var = lst_var->next;
	}
	return (NULL);
}

bool	is_valid_variable_name(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

static t_dlist	*import_in_env(t_dlist **lst_var, t_var var)
{
	if (get_var(*lst_var, var.name) == NULL)
	{
		if (!add_var(lst_var, var.name, var.value))
			return (NULL);
	}
	else
	{
		free(get_var(*lst_var, var.name)->value);
		get_var(*lst_var, var.name)->value = ft_strdup(var.value);
		get_var(*lst_var, var.name)->value_len = ft_strlen(var.value);
	}
	return (*lst_var);
}

t_dlist	*import_one_var(t_dlist **lst_var, char *value)
{
	size_t	j;
	t_var	var;

	j = 0;
	while (value[j] != '\0')
	{
		if (value[j] == '=')
		{
			var.name = &value[0];
			var.value = &value[j + 1];
			value[j] = '\0';
			break ;
		}
		j++;
	}
	if (!is_valid_variable_name(var.name))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: '%s=%s': not a valid identifier\n",
			var.name, var.value);
		return (*lst_var);
	}
	return (import_in_env(lst_var, var));
}
