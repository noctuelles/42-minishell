/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:41:35 by dhubleur         ###   ########.fr       */
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

void	free_all(t_command *cmd, t_dlist *env)
{
	t_command	*tmp;

	free_env(env);
	while (cmd)
	{
		tmp = cmd->next;
		free_cmd(cmd);
		cmd = tmp;
	}
}

int	execute_basic(char *str, int count, char **argv, t_dlist *env)
{
	int	res;

	if (strcmp(str, "echo") == 0)
		res = ft_echo(count, argv, env);
	if (strcmp(str, "cd") == 0)
		res = ft_cd(count, argv, env);
	if (strcmp(str, "pwd") == 0)
		res = ft_pwd(count, argv, env);
	if (strcmp(str, "export") == 0)
		res = ft_export(count, argv, env);
	if (strcmp(str, "unset") == 0)
		res = ft_unset(count, argv, env);
	if (strcmp(str, "env") == 0)
		res = ft_env(count, argv, env);
	return (res);
}

int	exec_builtin(t_command *command, t_minishell minishell,
	int save_stdin, int forking)
{
	int		count;
	char	*str;
	char	**argv;
	int		res;
	t_dlist	*env;

	env = minishell.vars;
	str = command->name;
	argv = command->args;
	count = 0;
	res = 0;
	while (argv[count])
		count++;
	res = execute_basic(str, count, argv, env);
	if (strcmp(str, "exit") == 0)
	{
		if (!forking)
			free_cmd(command);
		ft_exit(count, argv, minishell, save_stdin);
	}
	if (forking)
		free_all(command, env);
	return (res);
}
