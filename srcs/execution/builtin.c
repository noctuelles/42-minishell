/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 20:28:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	execute_basic(char *str, int count, char **argv, t_minishell *minishell)
{
	int	res;

	if (ft_strcmp(str, "echo") == 0)
		res = ft_echo(count, argv, minishell);
	if (ft_strcmp(str, "cd") == 0)
		res = ft_cd(count, argv, minishell);
	if (ft_strcmp(str, "pwd") == 0)
		res = ft_pwd(count, argv, minishell);
	if (ft_strcmp(str, "export") == 0)
		res = ft_export(count, argv, minishell);
	if (ft_strcmp(str, "unset") == 0)
		res = ft_unset(count, argv, minishell);
	if (ft_strcmp(str, "env") == 0)
		res = ft_env(count, argv, minishell);
	if (ft_strcmp(str, "exit") == 0)
		res = ft_exit(count, argv, minishell);
	return (res);
}

void	clean_everything(t_minishell *minishell)
{
	if (minishell->vars)
		free_env(minishell->vars);
	if (minishell->current_pipeline_first)
		free_cmd_pipeline(minishell->current_pipeline_first);
	if (minishell->root)
		ast_tree_delete_node(minishell->root);
	close(minishell->save_stdin);
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
	if (forking && ft_strcmp(str, "exit") != 0)
		clean_everything(minishell);
	return (res);
}
