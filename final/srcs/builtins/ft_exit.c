/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:10:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/07 14:29:49 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	end_program(int save_stdin, t_dlist *env, int exit_code)
{
	close(0);
	close(save_stdin);
	free_env(env);
	exit(exit_code);
	return (1);
}

void	init(int *exit_code, int argc, int save_stdin, t_dlist *env)
{
	*exit_code = 0;
	fprintf(stderr, "exit\n");
	if (argc == 1)
		end_program(save_stdin, env, *exit_code);
}

int	ft_exit(int argc, char **argv, t_dlist *env, int save_stdin)
{
	int	exit_code;
	int	i;

	init(&exit_code, argc, save_stdin, env);
	i = -1;
	while (argv[1][++i])
	{
		if (argv[1][i] >= '0' && argv[1][i] <= '9')
		{
			exit_code *= 10;
			exit_code += argv[1][i] - '0';
		}
		else
		{
			fprintf(stderr, "Minishell: exit: %s: numeric argument required\n",
				argv[1]);
			exit(1);
		}
	}
	if (argc > 2)
	{
		fprintf(stderr, "Minishell: exit: too many arguments\n");
		return (1);
	}
	return (end_program(save_stdin, env, exit_code));
}
