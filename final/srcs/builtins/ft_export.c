/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:38:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/17 14:27:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_export(int argc, char **argv, t_dlist *env)
{
	int	i;
	t_var	var;

	if(argc < 2)
	{
		printf("%s: please specify arguments\n", argv[0]);
		return (1);
	}
	i = 0;
	while(++i < argc)
	{
		if(strchr(argv[i], '='))
		{
			import_one_var(&env, argv[i]);
		}
		else
		{
			if(get_var(env, argv[i]) != NULL)
			{
				import_empty_var(&env, argv[i]);
			}
		}
	}
	return (0);
}