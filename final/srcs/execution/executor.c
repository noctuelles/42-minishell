/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:53:14 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/04 14:14:47 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

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

void	file_error(t_command *command, int *error)
{
	*error = 1;
	fprintf(stderr, "Minishell: %s: %s\n", command->in_name, strerror(command->in_errno));
}

void	close_all_error(t_command *command, int code)
{
	if (command->io_in_redirect > 0)
		close(command->io_in_redirect);
	if (command->io_out_redirect > 0)
		close(command->io_out_redirect);
	exit(code);
}

void	dup_for_redirections(t_command *command, int pid)
{
	int	error;

	error = 0;
	if (pid == 0)
	{
		if (command->io_in_redirect != -1)
		{
			if (command->io_in_redirect == -2)
				file_error(command, &error);
			else
				dup2(command->io_in_redirect, 0);
		}
		if (command->io_out_redirect != -1)
		{
			if (command->io_out_redirect == -2)
				file_error(command, &error);
			else
				dup2(command->io_out_redirect, 1);
		}
		if (error)
			close_all_error(command, -1);
	}
}

void	error_exit(char *str, int errno_value)
{
	fprintf(stderr, "Minishell: %s: %s", str, strerror(errno_value));
	exit(1);
}

int	execute_file(t_command *command, t_dlist *vars, int forking, int save_stdin)
{
	pid_t	pid;
	int		pipefd[2];

	if(command->name != NULL)
	{
		add_command_to_args(command);
		if(forking)
		{
			if ((command->is_piped && pipe(pipefd) < 0))
				error_exit("pipe error", errno);
			pid = fork();
			if (pid == -1)
				error_exit("fork error", errno);
			dup_for_pipe(command, pid, pipefd);
			dup_for_redirections(command, pid);
			if (pid == 0)
			{
				if(!is_builtin(command->original_name))
				{
					execve(command->name, command->args, export_env(vars));
					perror("Execution error");
					close_all_error(command, errno);
					return (1);
				}
				else
					exit(exec_builtin(command->name, command->args, vars, save_stdin));
			}
			else
			{
				command->pid = pid;
				return (4242);
			}
		}
		else
			return(exec_builtin(command->name, command->args, vars, save_stdin));
	}
	else
		return (127);
}
