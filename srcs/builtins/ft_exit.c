/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:10:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:32:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "ft_dprintf.h"

int	end_program(t_minishell *minishell, int exit_code)
{
	clean_everything(minishell);
	close(minishell->save_stdin);
	close(0);
	if (exit_code < 0)
		exit(minishell->last_ret);
	else
		exit(exit_code);
	return (1);
}

void	init(int argc, t_minishell *minishell)
{
	if (isatty(0) == 1)
		ft_dprintf(2, "exit\n");
	if (argc == 1)
		end_program(minishell, -1);
}

void	check_long(char **argv, t_minishell *minishell)
{
	if (argv[1][0] == '-' && (ft_strcmp(argv[1], "-9223372036854775808") > 0
		|| ft_strlen(argv[1]) > 20))
	{
		ft_dprintf(2, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
		minishell->last_ret = 2;
		end_program(minishell, -1);
	}
	if (argv[1][0] != '-' && (ft_strcmp(argv[1], "9223372036854775807") > 0
		|| ft_strlen(argv[1]) > 19))
	{
		ft_dprintf(2, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
		minishell->last_ret = 2;
		end_program(minishell, -1);
	}
}

void	exit_error(char **argv, t_minishell *minishell)
{
	ft_dprintf(2, EXIT_NUMERIC_REQUIRED, argv[0], argv[1]);
	clean_everything(minishell);
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
	exit_code = 0;
	while (argv[1][++i])
	{
		if (argv[1][i] >= '0' && argv[1][i] <= '9')
			exit_code = (exit_code * 10) + (argv[1][i] - '0');
		else
			exit_error(argv, minishell);
	}
	if (argc > 2)
	{
		ft_dprintf(2, EXIT_TO_MANY, argv[0]);
		return (1);
	}
	check_long(argv, minishell);
	return (end_program(minishell, exit_code));
}
