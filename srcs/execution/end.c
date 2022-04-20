/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:55:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/20 12:47:07 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"

void	free_for_end(t_minishell *minishell)
{
	(void)minishell;
}

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
				ft_dprintf(STDERR_FILENO, QUIT);
				g_sigint = 1;
			}
		}
		else if (__WCOREDUMP(wait_status))
			ft_dprintf(2, END_BY_SIGNAL, pid, WTERMSIG(wait_status));
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
	if (ret == 424242)
	{
		g_sigint = 1;
		return (0);
	}
	if (ret == 4242)
		count = 1;
	if (first->next == NULL)
	{
		if (ret != 4242)
		{
			*status = ret;
		}
		else
			*last_pid = first->pid;
	}
	*cmd = first->next;
	return (count);
}

int	wait_for_result(int count, int last_pid, int status)
{
	size_t	i;
	int		pid;
	int		wait_status;

	i = 0;
	while (i < (size_t) count)
	{
		pid = waitpid(-1, &wait_status, 0);
		close(STDIN_FILENO);
		treat_result(pid, wait_status, &status, last_pid);
		i++;
	}
	return (status);
}

int	pipeline_clean(t_minishell *minishell, int code)
{
	set_signals_as_prompt();
	g_sigint = 0;
	dup2(minishell->save_stdin, 0);
	close(minishell->save_stdin);
	free_cmd_pipeline(minishell->current_pipeline_first);
	minishell->current_pipeline_first = NULL;
	return (code);
}
