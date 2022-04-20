/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:37:58 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/20 13:38:41 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ft_dprintf.h"

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
	if (fd1 > 0)
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
	ft_dprintf(2, ERROR_ERRNO, str, strerror(errno_value));
	exit(1);
}
