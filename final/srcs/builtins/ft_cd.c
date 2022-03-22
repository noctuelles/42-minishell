/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:04:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/22 14:44:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_cd(int argc, char **argv, t_dlist *env)
{
	char *pwd;
	char *old_pwd;
	
	if(argc != 2)
	{
		printf("%s: use with format: cd <relative or absolute path>\n", argv[0]);
		return 1;
	}
	if(chdir(argv[1]) == 0)
	{
		old_pwd = get_var(env, "PWD")->value;
		pwd = calloc(sizeof(char), 1000);
		pwd = getcwd(pwd, 1000);
		if(!pwd)
		{
			perror("cd: get working directory error");
			return 1;
		}
		if(get_var(env, "OLDPWD") != NULL)
			get_var(env, "OLDPWD")->value = old_pwd;
		else
			import_one_var(&env, strcat(strdup("OLDPWD="), old_pwd));
		get_var(env, "OLDPWD")->value_len = strlen(old_pwd);
		if(get_var(env, "PWD") != NULL)
			get_var(env, "PWD")->value = pwd;
		else
			import_one_var(&env, strcat(strdup("PWD="), pwd));
		get_var(env, "PWD")->value_len = strlen(pwd);
		return 0;
	}
	perror("");
	return 1;
}