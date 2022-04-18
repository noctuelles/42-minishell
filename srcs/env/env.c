/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:08:51 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 13:53:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include <errno.h>

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

int	get_current_working_dir(char **cwd)
{
	size_t	buff_size;

	buff_size = 100;
	*cwd = (char *) malloc(buff_size * sizeof(char));
	if (!*cwd)
		return (-1);
	*cwd = getcwd(*cwd, buff_size);
	while (*cwd == NULL)
	{
		free(*cwd);
		if (errno == ERANGE)
		{
			buff_size *= 2;
			*cwd = (char *) malloc(buff_size * sizeof(char));
			if (!*cwd)
				return (-1);
		}
		else
			return (-2);
		*cwd = getcwd(*cwd, buff_size);
	}
	return (0);
}

int	refill_env(t_dlist **env)
{
	int		retcode;
	char	*cwd;

	retcode = 0;
	if (get_var(*env, "PWD") == NULL)
	{
		retcode = get_current_working_dir(&cwd);
		if (retcode == 0)
		{
			if (!add_var(env, "PWD", cwd))
				retcode = -1;
		}
		free(cwd);
	}
	if (retcode == -1)
		display_error_more(STR_MALLOC);
	else if (retcode == -2)
		display_error_more(STR_GETCWD);
	return (retcode);
}
