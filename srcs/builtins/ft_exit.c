/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:10:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/12 17:30:27 by dhubleur         ###   ########.fr       */
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

void	init(long int *exit_code, int argc, int save_stdin, t_minishell minishell)
{
	t_dlist *env;
	
	env = minishell.vars;
	*exit_code = minishell.last_ret;
	if(isatty(0) == 1)
		fprintf(stderr, "exit\n");
	if (argc == 1)
		end_program(save_stdin, env, *exit_code);
}

void	check_long(char **argv, int save_stdin, t_dlist *env)
{
	if (argv[1][0] == '-' && (strcmp(argv[1], "-9223372036854775808") > 0
		|| strlen(argv[1]) > 20))
	{
		fprintf(stderr, "Minishell: exit: %s: numeric argument required\n",
			argv[1]);
		end_program(save_stdin, env, 2);
	}
	if (argv[1][0] != '-' && (strcmp(argv[1], "9223372036854775807") > 0
		|| strlen(argv[1]) > 19))
	{
		fprintf(stderr, "Minishell: exit: %s: numeric argument required\n",
			argv[1]);
		end_program(save_stdin, env, 2);
	}
}

int	ft_exit(int argc, char **argv, t_minishell minishell, int save_stdin)
{
	long int	exit_code;
	int			i;
	t_dlist		*env;

	env = minishell.vars;
	init(&exit_code, argc, save_stdin, minishell);
	i = -1;
	if (argv[1][i + 1] == '-')
		i++;
	while (argv[1][++i])
	{
		if (argv[1][i] >= '0' && argv[1][i] <= '9')
			exit_code = (exit_code * 10) + (argv[1][i] - '0');
		else
		{
			fprintf(stderr, "Minishell: exit: %s: numeric argument required\n",
				argv[1]);
			free_env(env);
			exit(1);
		}
	}
	if (argc > 2)
	{
		fprintf(stderr, "Minishell: exit: too many arguments\n");
		return (1);
	}
	check_long(argv, save_stdin, env);
	return (end_program(save_stdin, env, exit_code));
}
