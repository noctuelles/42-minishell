/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/17 14:14:58 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_echo(int argc, char **argv, t_dlist *env)
{
	int	is_option;
	int	i;

	is_option = 0;
	if(argc > 1 && strcmp(argv[1], "-n") == 0)
	{
		is_option = 1;
		i = 1;
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