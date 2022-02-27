/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:04:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 18:43:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_cd(int argc, char **argv, t_env **env)
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
		old_pwd = get_value(env, "PWD");
		pwd = calloc(sizeof(char), 1000);
		pwd = getcwd(pwd, 1000);
		if(!pwd)
		{
			perror("cd: get working directory error");
			return 1;
		}
		env_update(env, "OLDPWD", old_pwd);
		env_update(env, "PWD", pwd);
		return 0;
	}
	perror("cd: path error");
	return 1;
}