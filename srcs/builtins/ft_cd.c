/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:04:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:29:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "ft_dprintf.h"
#include "builtins.h"

void	update_env(char *pwd, char *old_pwd, t_minishell *minishell)
{
	if (get_var(minishell->vars, "OLDPWD") != NULL)
	{
		free(get_var(minishell->vars, "OLDPWD")->value);
		get_var(minishell->vars, "OLDPWD")->value = old_pwd;
	}
	else
	{
		add_var(&(minishell->vars), "OLDPWD", old_pwd);
	}
	get_var(minishell->vars, "OLDPWD")->value_len = ft_strlen(old_pwd);
	if (get_var(minishell->vars, "PWD") != NULL)
	{
		get_var(minishell->vars, "PWD")->value = pwd;
	}
	else
		add_var(&(minishell->vars), "PWD", pwd);
	get_var(minishell->vars, "PWD")->value_len = ft_strlen(pwd);
}

int	ft_cd(int argc, char **argv, t_minishell *minishell)
{
	char	*pwd;
	char	*old_pwd;
	t_dlist	*env;

	env = minishell->vars;
	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, CD_FORMAT_ERROR, argv[0], argv[0]);
		return (1);
	}
	if (chdir(argv[1]) == 0)
	{
		old_pwd = get_var(env, "PWD")->value;
		if (get_current_working_dir(&pwd) != 0)
		{
			ft_dprintf(STDERR_FILENO, ERROR_ERRNO, argv[0], strerror(errno));
			return (1);
		}
		update_env(pwd, old_pwd, minishell);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, ERROR_ERRNO, argv[0], strerror(errno));
	return (1);
}
