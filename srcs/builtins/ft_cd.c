/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:04:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 11:08:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

void	update_env(char *pwd, char *old_pwd, t_dlist *env)
{
	if (get_var(env, "OLDPWD") != NULL)
	{
		free(get_var(env, "OLDPWD")->value);
		get_var(env, "OLDPWD")->value = old_pwd;
	}
	else
		import_one_var(&env, ft_strcat(ft_strdup("OLDPWD="), old_pwd));
	get_var(env, "OLDPWD")->value_len = ft_strlen(old_pwd);
	if (get_var(env, "PWD") != NULL)
	{
		get_var(env, "PWD")->value = pwd;
	}
	else
		import_one_var(&env, ft_strcat(ft_strdup("PWD="), pwd));
	get_var(env, "PWD")->value_len = ft_strlen(pwd);
}

int	ft_cd(int argc, char **argv, t_minishell *minishell)
{
	char	*pwd;
	char	*old_pwd;
	t_dlist	*env;

	env = minishell->vars;
	if (argc != 2)
	{
		ft_printf(CD_FORMAT_ERROR, argv[0], argv[0]);
		return (1);
	}
	if (chdir(argv[1]) == 0)
	{
		old_pwd = get_var(env, "PWD")->value;
		if (get_current_working_dir(&pwd) != 0)
		{
			ft_printf(ERROR_ERRNO, argv[0], strerror(errno));
			return (1);
		}
		update_env(pwd, old_pwd, env);
		return (0);
	}
	ft_printf(ERROR_ERRNO, argv[0], strerror(errno));
	return (1);
}
