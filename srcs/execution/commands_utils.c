/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:05:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/19 18:05:24 by plouvel          ###   ########.fr       */
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

