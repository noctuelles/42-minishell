/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:08:51 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 13:22:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h> 

static char	*fill_envp_str(char **str, t_var var)
{
	size_t	env_var_len;

	env_var_len = var.name_len + var.value_len + 2;
	*str = (char *) malloc((env_var_len + 1) * sizeof(char));
	if (!*str)
		return (NULL);
	(*str)[0] = '\0';
	ft_strcat(*str, var.name);
	ft_strcat(*str, "=");
	ft_strcat(*str, var.value);
	return (*str);
}

char	**free_envp(char **envp, size_t i)
{
	size_t	n;

	n = 0;
	if (i == 0)
	{
		while (envp[n])
			free(envp[n++]);
	}
	else
	{
		while (n < i)
			free(envp[n++]);
	}
	free(envp);
	return (NULL);
}

char	**export_env(t_dlist *lst)
{
	size_t	i;
	t_var	var;
	char	**envp;

	envp = (char **) malloc((ft_dlstsize(lst) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (lst)
	{
		var = *(t_var *) lst->content;
		if (!fill_envp_str(&envp[i], var))
			return (free_envp(envp, i));
		i++;
		lst = lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
