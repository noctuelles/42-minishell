/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:10:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/17 16:43:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	end_program(t_minishell *minishell)
{
	close(0);
	close(minishell->save_stdin);
	free_env(minishell->vars);
	exit(minishell->last_ret);
	return (1);
}

void	init(int argc, t_minishell *minishell)
{
	if (isatty(0) == 1)
		fprintf(stderr, "exit\n");
	if (argc == 1)
		end_program(minishell);
}

void	check_long(char **argv, t_minishell *minishell)
{
	if (argv[1][0] == '-' && (strcmp(argv[1], "-9223372036854775808") > 0
		|| strlen(argv[1]) > 20))
	{
		fprintf(stderr, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
		minishell->last_ret = 2;
		end_program(minishell);
	}
	if (argv[1][0] != '-' && (strcmp(argv[1], "9223372036854775807") > 0
		|| strlen(argv[1]) > 19))
	{
		fprintf(stderr, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
		minishell->last_ret = 2;
		end_program(minishell);
	}
}

void	exit_error(char **argv, t_minishell *minishell)
{
	fprintf(stderr, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
	free_env(minishell->vars);
	exit(1);
}

int	ft_exit(int argc, char **argv, t_minishell *minishell)
{
	long int	exit_code;
	int			i;

	init(argc, minishell);
	i = -1;
	if (argv[1][i + 1] == '-')
		i++;
	while (argv[1][++i])
	{
		if (argv[1][i] >= '0' && argv[1][i] <= '9')
			exit_code = (exit_code * 10) + (argv[1][i] - '0');
		else
			exit_error(argv, minishell);
	}
	if (argc > 2)
	{
		fprintf(stderr, EXIT_TO_MANY, argv[0]);
		return (1);
	}
	check_long(argv, minishell);
	return (end_program(minishell));
}
