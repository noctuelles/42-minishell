/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:53:14 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/18 13:37:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_for_pipe(t_command *command, int pid, int pipefd[2])
{
	if (command->is_piped)
	{
		if (pid == 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		else
		{
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}
}

void	close_all_error(t_command *command, int code)
{
	if (command->io_in_fd > 0)
		close(command->io_in_fd);
	if (command->io_out_fd > 0)
		close(command->io_out_fd);
	exit(code);
}

void	dup_and_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	if(fd1 > 0)
		close(fd1);
}

void	dup_for_redirections(t_command *command, int pid)
{
	int	error;

	error = 0;
	if (pid == 0)
	{
		if (command->io_in_fd != -1)
		{
			dup_and_close(command->io_in_fd, 0);
		}
		if (command->io_out_fd != -1)
		{
			dup_and_close(command->io_out_fd, 1);
		}
		if (error)
			close_all_error(command, -1);
	}
}

void	error_exit(char *str, int errno_value)
{
	fprintf(stderr, ERROR_ERRNO, str, strerror(errno_value));
	exit(1);
}

void	pipe_and_fork(int pipefd[2], t_command *command, int *pid)
{
	if ((command->is_piped && pipe(pipefd) < 0))
		error_exit(PIPE_ERROR, errno);
	*pid = fork();
	if (*pid == -1)
		error_exit(FORK_ERROR, errno);
	dup_for_pipe(command, *pid, pipefd);
	dup_for_redirections(command, *pid);
	if (*pid != 0)
		command->pid = *pid;
}

void	executing(t_command *command, t_minishell *minishell)
{
	if (!is_builtin(command->args[0]))
	{
		execve(command->name, command->args, export_env(minishell->vars));
		perror(EXECUTION_ERROR);
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
	if(save_stdout > 0)
		close(save_stdout);
	return (ret);
}

int	execute_file(t_command *command, t_minishell *minishell, int forking)
{
	pid_t	pid;
	int		pipefd[2];

	if(!prepare_fd(command))
		return (1);
	if (command->name != NULL)
	{
		if (forking)
		{
			pipe_and_fork(pipefd, command, &pid);
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
	{
		if(forking)
		{
			pipe(pipefd);
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if(command->empty_command)
			return (1);
		else
			return (127);
	}
}
