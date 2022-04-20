/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:05:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 13:21:01 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_command	*init_cmd(void)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->here_doc = -1;
	return (command);
}

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
	ft_dlstclear(&cmd->io_in, NULL);
	ft_dlstclear(&cmd->io_out, NULL);
	free(cmd);
}

void	free_cmd_pipeline(t_command *first)
{
	t_command	*tmp;

	while (first != NULL)
	{
		tmp = first->next;
		free_cmd(first);
		first = tmp;
	}
}
