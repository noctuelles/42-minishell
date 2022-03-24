/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:10:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/24 16:18:59 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_exit(int argc, char **argv, t_dlist *env, int save_stdin)
{
	if(argc > 2)
	{
		fprintf(stderr, "Minishell: exit: too many arguments\n");
		return 1;
	}
	close(0);
	close(save_stdin);
	free_env(env);
	if(argc == 1)
	{
		printf("exit\n");
		exit(0);
	}
	int exit_code = 0;
	for(int i = 0; argv[1][i]; i++)
	{
		if(argv[1][i] >= '0' && argv[1][i] <= '9')
		{
			exit_code *= 10;
			exit_code += argv[1][i] - '0';
		}
		else
		{
			printf("exit\n");
			fprintf(stderr, "bash: exit: %s: numeric argument required\n", argv[1]);
			exit(1);
		}
	}
	printf("exit\n");
	exit(exit_code);
}