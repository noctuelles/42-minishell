/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/17 14:36:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	if (strcmp(str, "cd") == 0)
		return (1);
	if (strcmp(str, "pwd") == 0)
		return (1);
	if (strcmp(str, "export") == 0)
		return (1);
	if (strcmp(str, "unset") == 0)
		return (1);
	if (strcmp(str, "env") == 0)
		return (1);
	if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	free_all(t_command *cmd, t_minishell *minishell)
{
	t_command	*tmp;

	free_env(minishell->vars);
	while (cmd)
	{
		tmp = cmd->next;
		free_cmd(cmd);
		cmd = tmp;
	}
}

int	execute_basic(char *str, int count, char **argv, t_minishell *minishell)
{
	int	res;

	if (strcmp(str, "echo") == 0)
		res = ft_echo(count, argv, minishell);
	if (strcmp(str, "cd") == 0)
		res = ft_cd(count, argv, minishell);
	if (strcmp(str, "pwd") == 0)
		res = ft_pwd(count, argv, minishell);
	if (strcmp(str, "export") == 0)
		res = ft_export(count, argv, minishell);
	if (strcmp(str, "unset") == 0)
		res = ft_unset(count, argv, minishell);
	if (strcmp(str, "env") == 0)
		res = ft_env(count, argv, minishell);
	return (res);
}

int	exec_builtin(t_command *command, t_minishell *minishell, int forking)
{
	int		count;
	char	*str;
	char	**argv;
	int		res;

	str = command->name;
	argv = command->args;
	count = 0;
	res = 0;
	while (argv[count])
		count++;
	res = execute_basic(str, count, argv, minishell);
	if (strcmp(str, "exit") == 0)
	{
		if (!forking)
			free_cmd(command);
		ft_exit(count, argv, minishell);
	}
	if (forking)
		free_all(command, minishell);
	return (res);
}
