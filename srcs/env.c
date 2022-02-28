/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:08:51 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 20:10:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h> 

static size_t	get_env_var_nbr(t_dlist *lst)
{
	size_t	nbr;
	t_var	var;

	nbr = 0;
	while (lst)
	{
		var = * (t_var *) lst->content;
		if (var.env_var == TRUE)
			nbr++;
		lst = lst->next;
	}
	return (nbr);
}

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

char	**gen_envp(t_dlist *lst)
{
	size_t	envp_size;
	size_t	i;
	t_var	var;
	char	**envp;

	envp_size = get_env_var_nbr(lst);
	envp = (char **) malloc((envp_size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (lst)
	{
		var = * (t_var *) lst->content;
		if (var.env_var)
		{
			if (!fill_envp_str(&envp[i], var))
				return (NULL);
		}
		i++;
		lst = lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
