/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_preparator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/18 15:46:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_in(t_arg *arg, t_command *command)
{
	if(command->io_in_fd != -1)
		close(command->io_in_fd);
	command->io_in_fd = open(arg->value, O_RDONLY);
	if(command->io_in_fd < 0)
	{
		fprintf(stderr, ERROR_ERRNO, arg->value, strerror(errno));
		return (0);
	}
	return (1);
}

int	open_out(t_arg *arg, t_command *command)
{
	if(command->io_out_fd != -1)
	{
		close(command->io_out_fd);
	}
	if(arg->type == ARG_REDIRECT_FILE)
		command->io_out_fd = open(arg->value, O_WRONLY | O_CREAT, 0644);
	else
		command->io_out_fd = open(arg->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(command->io_out_fd < 0)
	{
		fprintf(stderr, ERROR_ERRNO, arg->value, strerror(errno));
		return (0);
	}
	return (1);
}

int	prepare_fd(t_command *command)
{
	t_dlist	*elem;
	t_arg	*arg;

	command->io_in_fd = -1;
	command->io_out_fd = -1;
	if(command->here_doc > 0)
	{
		command->io_in_fd = command->here_doc;
		command->here_doc = -1;
	}
	else
	{
		elem = command->io_in;
		if(elem)
		{
			arg = elem->content;
			while(elem->next != NULL)
			{
				if(!open_in(arg, command))
					return (0);
				elem = elem->next;
				arg = elem->content;
			}
			if(!open_in(arg, command))
				return (0);
		}
	}
	elem = command->io_out;
	if(elem)
	{
		arg = elem->content;
		while(elem->next != NULL)
		{
			if(!open_out(arg, command))
				return (0);
			elem = elem->next;
			arg = elem->content;
		}
		if(!open_out(arg, command))
			return (0);
	}
	return (1);
}