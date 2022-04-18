/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:55:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/18 20:18:13 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_cmd(t_command *cmd)
{
	if (cmd->name && cmd->is_name_malloc)
		free(cmd->name);
	free(cmd->args);
	if (cmd->io_in_fd > 0)
		close(cmd->io_in_fd);
	if (cmd->io_out_fd > 0)
		close(cmd->io_out_fd);
	if (cmd->here_doc > 0)
		close(cmd->here_doc);
	ft_dlstclear(&(cmd->io_in), NULL);
	ft_dlstclear(&(cmd->io_out), NULL);
	free(cmd);
}

void	free_command_pipeline(t_command *first)
{
	t_command	*tmp;

	while (first != NULL)
	{
		tmp = first->next;
		free_cmd(first);
		first = tmp;
	}
}

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
	int	i;
	int	pid;
	int	wait_status;

	i = -1;
	while (++i < count)
	{
		pid = waitpid(-1, &wait_status, 0);
		close(0);
		treat_result(pid, wait_status, &status, last_pid);
	}
	return (status);
}

int	pipeline_clean(t_minishell *minishell, int code)
{
	set_signals_as_prompt();
	g_sigint = 0;
	dup2(minishell->save_stdin, 0);
	close(minishell->save_stdin);
	free_command_pipeline(minishell->current_pipeline_first);
	minishell->current_pipeline_first = NULL;
	return (code);
}