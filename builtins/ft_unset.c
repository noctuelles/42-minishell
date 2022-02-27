/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:05:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 14:18:34 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_unset(int argc, char **argv, t_env **env)
{
	int	i;
	
	if (argc < 2)
	{
		printf("%s: not enough arguments\n", argv[0]);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if(is_var_with_name(env, argv[i]))
			remove_var(env, argv[i]);
	}
	return (0);
}