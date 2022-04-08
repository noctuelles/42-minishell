/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:04:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/07 11:48:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>

void	update_env(char *pwd, char *old_pwd, t_dlist *env)
{
	if (get_var(env, "OLDPWD") != NULL)
		get_var(env, "OLDPWD")->value = old_pwd;
	else
		import_one_var(&env, strcat(strdup("OLDPWD="), old_pwd));
	get_var(env, "OLDPWD")->value_len = strlen(old_pwd);
	if (get_var(env, "PWD") != NULL)
		get_var(env, "PWD")->value = pwd;
	else
		import_one_var(&env, strcat(strdup("PWD="), pwd));
	get_var(env, "PWD")->value_len = strlen(pwd);
}

int	ft_cd(int argc, char **argv, t_dlist *env)
{
	char	*pwd;
	char	*old_pwd;

	if (argc != 2)
	{
		printf("Minishell: %s: use with format: \
			cd <relative or absolute path>\n",argv[0]);
		return (1);
	}
	if (chdir(argv[1]) == 0)
	{
		old_pwd = get_var(env, "PWD")->value;
		pwd = calloc(sizeof(char), 1000);
		pwd = getcwd(pwd, 1000);
		if (!pwd)
		{
			printf("Minishell: %s: %s\n", argv[0], strerror(errno));
			return (1);
		}
		update_env(pwd, old_pwd, env);
		return (0);
	}
	printf("Minishell: %s: %s\n", argv[0], strerror(errno));
	return (1);
}