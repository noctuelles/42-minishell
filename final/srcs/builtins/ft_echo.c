/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/29 16:45:06 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int is_option_string(char *str)
{
	int	i;

	if(str[0] != '-')
		return (0);
	i = 0;
	while(str[++i])
	{
		if(str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(int argc, char **argv, t_dlist *env)
{
	(void) env;
	int	is_option;
	int	i;

	is_option = 0;
	if(argc > 1 && is_option_string(argv[1]))
	{
		is_option = 1;
		i = 1;
		while(i < argc && is_option_string(argv[i]))
			i++;
		i--;
	}
	else
		i = 0;
	while(++i < argc)
	{
		printf("%s", argv[i]);
		if(i < argc - 1)
			printf(" ");
	}
	if(!is_option)
		printf("\n");
	return 0;
}