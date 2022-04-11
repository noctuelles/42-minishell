/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/11 17:04:57 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

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

int	ft_cd(int argc, char **argv, t_dlist *env);
int	ft_echo(int argc, char **argv, t_dlist *env);
int	ft_env(int argc, char **argv, t_dlist *env);
int	ft_export(int argc, char **argv, t_dlist *env);
int	ft_pwd(int argc, char **argv, t_dlist *env);
int	ft_unset(int argc, char **argv, t_dlist *env);
int	ft_exit(int argc, char **argv, t_dlist *env, int save_stdin);

void	free_cmd(t_command *cmd);

int	exec_builtin(t_command *command, t_dlist *env, int save_stdin, int forking)
{
	int	count;
	char	*str;
	char	**argv;

	str = command->name;
	argv = command->args;
	count = 0;
	while (argv[count])
		count++;
	if (strcmp(str, "echo") == 0)
		return (ft_echo(count, argv, env));
	if (strcmp(str, "cd") == 0)
		return (ft_cd(count, argv, env));
	if (strcmp(str, "pwd") == 0)
		return (ft_pwd(count, argv, env));
	if (strcmp(str, "export") == 0)
		return (ft_export(count, argv, env));
	if (strcmp(str, "unset") == 0)
		return (ft_unset(count, argv, env));
	if (strcmp(str, "env") == 0)
		return (ft_env(count, argv, env));
	if (strcmp(str, "exit") == 0)
	{
		if(!forking)
			free_cmd(command);
		ft_exit(count, argv, env, save_stdin);
	}
	return ((0));
}
