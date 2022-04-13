/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:55:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:59:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	treat_result(int pid, int wait_status, int *pipeline_result,
	int last_pid)
{
	if (WIFEXITED(wait_status))
	{
		if (last_pid != 0 && pid == last_pid)
			*pipeline_result = WEXITSTATUS(wait_status);
	}
	else if (WIFSIGNALED(wait_status))
	{
		if (WTERMSIG(wait_status) == 3)
		{
			if (!g_sigint)
			{
				fprintf(stderr, QUIT);
				g_sigint = 1;
			}
		}
		else if (__WCOREDUMP(wait_status))
			fprintf(stderr, END_BY_SIGNAL, pid, WTERMSIG(wait_status));
		if (last_pid != 0 && pid == last_pid)
			*pipeline_result = 128 + WTERMSIG(wait_status);
	}
}

int	treat_return_code(t_command **cmd, int ret, int *status, int *last_pid)
{
	int			count;
	t_command	*first;

	first = *cmd;
	count = 0;
	if (ret == 4242)
		count = 1;
	if (first->next == NULL)
	{
		if (ret != 4242)
			*status = ret;
		else
			*last_pid = first->pid;
	}
	*cmd = first->next;
	free_cmd(first);
	return (count);
}

int	end_pipeline(int save_stdin, int status)
{
	set_signals_as_prompt();
	g_sigint = 0;
	close(0);
	dup2(save_stdin, 0);
	close(save_stdin);
	return (status);
}

int	cancel_everything(int save_stdin, t_command *cmd)
{
	t_command	*tmp;

	g_sigint = 0;
	dup2(save_stdin, 0);
	close(save_stdin);
	while (cmd)
	{
		tmp = cmd->next;
		free_cmd(cmd);
		cmd = tmp;
	}
	return (130);
}

int	wait_for_result(int count, int last_pid)
{
	int	i;
	int	pid;
	int	wait_status;
	int	status;

	i = -1;
	status = 0;
	while (++i < count)
	{
		pid = waitpid(-1, &wait_status, 0);
		close(0);
		treat_result(pid, wait_status, &status, last_pid);
	}
	return (status);
}
