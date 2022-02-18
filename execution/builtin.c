/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:32:27 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 19:32:27 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	is_builtin(char *str)
{
	if(strcmp(str, "echo") == 0)
		return 1;
	if(strcmp(str, "cd") == 0)
		return 1;
	if(strcmp(str, "pwd") == 0)
		return 1;
	if(strcmp(str, "export") == 0)
		return 1;
	if(strcmp(str, "unset") == 0)
		return 1;
	if(strcmp(str, "env") == 0)
		return 1;
	if(strcmp(str, "exit") == 0)
		return 1;
	return 0;
}