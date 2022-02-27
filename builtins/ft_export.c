/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:38:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 17:13:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_export(int argc, char **argv, t_env **env)
{
	int	i;
	t_env *env_elem;

	if(argc < 2)
	{
		printf("%s: please specify arguments\n", argv[0]);
		return (1);
	}
	i = 0;
	while(++i < argc)
	{
		env_elem = NULL;
		if(strchr(argv[i], '='))
		{
			env_elem = get_env_element(argv[i]);
			if (!env_elem)
				return 1;
		}
		else
		{
			if(!is_var_with_name(env, argv[i]))
			{
				env_elem = malloc(sizeof(t_env));
				if(!env_elem)
					return 1;
				env_elem->name = argv[i];
				env_elem->value = strdup("");
			}
		}
		if(env_elem)
			add_var(env, env_elem);
	}
	return (0);
}