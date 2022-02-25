/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:30:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 02:06:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_env_var
{
	char	*name;
	char	*value;
	t_bool	inherit;
} t_env_var;

typedef struct s_minishell
{
	t_dlist	*dlst_var;
} t_minishell;

t_dlist	*add_env_var(t_dlist **lst_var, char *name, char *value, t_bool inherit)
{
	t_env_var	*env_var;
	t_dlist		*elem;

	env_var = (t_env_var *) malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	elem = ft_dlstnew(env_var);
	if (!elem)
	{
		free(env_var);
		return (NULL);
	}
	env_var->name = name;
	env_var->value = value;
	env_var->inherit = inherit;
	elem->content = (void *) env_var;
	ft_dlstadd_back(lst_var, elem);
}

static void	free_env_var(void *dlst_content)
{
	t_env_var	*env_var;

	env_var = (t_env_var *) dlst_content;
	if (env_var->inherit == FALSE)
	{
		free(env_var->name);
		free(env_var->content);
	}
	free(env_var);
}

void	del_env_var(t_dlist **lst_var, char *name)
{
	t_dlist		*elem;
	t_env_var	*env_var;

	elem = *lst_var;
	while (elem)
	{
		env_var = (t_env_var *) elem->content;
		if (ft_strcmp(env_var->name, name) == 0)
			break ;
		elem = elem->next;
	}
	ft_dlstdelone(lst_var, elem, &free_env_var);
}

char	*get_env_var_value(t_dlist *lst_var, char *name)
{
	t_env_var	*env_var;

	while (lst_var)
	{
		env_var = (t_env_var *) lst_var->content;
		if (ft_strcmp(env_var->name, name) == 0)
			return (env_var->value);
		lst_var = lst_var->next;
	}
	return (NULL);
}
