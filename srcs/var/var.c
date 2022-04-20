/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 16:07:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ft_dprintf.h"
#include <stdbool.h>
#include <stdlib.h>

t_dlist	*add_var(t_dlist **lst_var, char *name, char *value)
{
	t_var	*var;
	t_dlist	*elem;

	var = (t_var *) ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	if (!var->name || !var->value)
	{
		free_var(var);
		return (NULL);
	}
	var->name_len = ft_strlen(name);
	var->value_len = ft_strlen(value);
	elem = ft_dlstnew(var);
	if (!elem)
	{
		free_var(var);
		return (NULL);
	}
	ft_dlstadd_back(lst_var, elem);
	return (*lst_var);
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

t_dlist	*import_var(t_minishell *minishell, char **envp)
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
		if (!add_var(&minishell->vars, var.name, var.value))
			return (set_minishell_err_null(minishell, ERR_MALLOC));
		i++;
	}
	return (minishell->vars);
}

/* free_var() free a given variable.
 * It doesn't try to free his name and value if the variable is inherited from
 * the execution environnement. */

void	free_var(void *dlst_content)
{
	t_var	*var;

	var = (t_var *) dlst_content;
	free(var->name);
	free(var->value);
	free(var);
}

void	free_env(t_dlist *env)
{
	t_dlist	*tmp;

	while (env != NULL)
	{
		free_var(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
