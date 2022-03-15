/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/15 14:52:25 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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