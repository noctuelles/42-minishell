/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */ /*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:30:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/01 15:01:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

t_dlist	*add_var(t_dlist **lst_var, t_var add_var)
{
	t_var	*var;
	t_dlist	*elem;

	var = (t_var *) malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	elem = ft_dlstnew(var);
	if (!elem)
	{
		free(var);
		return (NULL);
	}
	var->name = strdup(add_var.name);
	var->name_len = ft_strlen(add_var.name);
	var->value = strdup(add_var.value);
	var->value_len = ft_strlen(add_var.value);
	var->inherit = add_var.inherit;
	elem->content = (void *) var;
	ft_dlstadd_back(lst_var, elem);
	return (*lst_var);
}

/* free_var() free a given variable.
 * It doesn't try to free his name and value if the variable is inherited from
 * the execution environnement. */

void	free_var(void *dlst_content)
{
	t_var	*var;

	var = (t_var *) dlst_content;
	if (var->inherit == FALSE)
	{
		free(var->name);
		free(var->value);
	}
	free(var);
}

/* del_var() try to delete the variable whose name is passed as an argument.
 * If the variable doesn't exist, it does nothing. */

void	del_var(t_dlist **lst_var, char *name)
{
	t_dlist		*elem;
	t_var		*var;

	elem = *lst_var;
	while (elem)
	{
		var = (t_var *) elem->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			ft_dlstdelone(lst_var, elem, &free_var);
			return ;
		}
		elem = elem->next;
	}
}

/* import_var() imports all environnement variable from envp.
 * envp is considered to be the paremeters implicitly passed to main()
 * routine. */

t_dlist	*import_var(t_dlist **lst_var, char **envp)
{
	size_t	i;
	size_t	j;
	t_var	var;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				var.name = &envp[i][0];
				var.value = &envp[i][j + 1];
				envp[i][j] = '\0';
			}
			j++;
		}
		var.inherit = TRUE;
		if (!add_var(lst_var, var))
			return (NULL);
		i++;
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
		}
		j++;
	}
	var.inherit = FALSE;
	if(get_var(*lst_var, var.name) == NULL)
	{
		if (!add_var(lst_var, var))
			return (NULL);
	}
	else
	{
		get_var(*lst_var, var.name)->value = strdup(var.value);
		get_var(*lst_var, var.name)->value_len = strlen(var.value);
	}
	return (*lst_var);
}

t_dlist	*import_empty_var(t_dlist **lst_var, char *name)
{
	t_var	var;


	var.name = name;
	var.value = "";
	var.inherit = FALSE;
	if (!add_var(lst_var, var))
		return (NULL);
	
	return (*lst_var);
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
