/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:53:14 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/20 13:38:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

int	pipe_and_fork(int pipefd[2], t_command *command, int *pid)
{
	if ((command->is_piped && pipe(pipefd) < 0))
	{
		display_error_more(NULL, "pipe", 0);
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		display_error_more(NULL, "fork", 0);
		return (0);
	}
	dup_for_pipe(command, *pid, pipefd);
	dup_for_redirections(command, *pid);
	if (*pid != 0)
		command->pid = *pid;
	return (1);
}

void	executing(t_command *command, t_minishell *minishell)
{
	if (!is_builtin(command->args[0]))
	{
		execve(command->name, command->args, export_env(minishell->vars));
		perror(STR_EXEC_ERROR);
		close_all_error(command, errno);
	}
	else
	{
		minishell->last_ret = 1;
		exit(exec_builtin(command, minishell, 1));
	}
}

int	simple_builtin(t_command *command, t_minishell *minishell)
{
	int	save_stdout;
	int	ret;

	save_stdout = -1;
	if (command->io_out_fd != -1)
	{
		save_stdout = dup(1);
		dup2(command->io_out_fd, 1);
		close(command->io_out_fd);
	}
	ret = exec_builtin(command, minishell, 0);
	dup2(save_stdout, 1);
	if (save_stdout > 0)
		close(save_stdout);
	return (ret);
}

int	null_command(int forking, t_command *command)
{
	int		pipefd[2];

	if (forking)
	{
		if (pipe(pipefd) < 0)
			return (424242);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (command->empty_command)
		return (1);
	else
		return (127);
}

int	execute_file(t_command *command, t_minishell *minishell, int forking)
{
	pid_t	pid;
	int		pipefd[2];

	if (!prepare_fd(command))
		return (1);
	if (command->name != NULL)
	{
		if (forking)
		{
			if (pipe_and_fork(pipefd, command, &pid) == 0)
				return (424242);
			if (pid == 0)
			{
				executing(command, minishell);
				return (1);
			}
			else
				return (4242);
		}
		else
			return (simple_builtin(command, minishell));
	}
	else
		return (null_command(forking, command));
}
