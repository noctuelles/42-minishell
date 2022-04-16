/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:05:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:26:49 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(int argc, char **argv, t_dlist *env)
{
	int	i;

	if (argc < 2)
	{
		printf(UNSET_NOT_ENOUGH, argv[0]);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (get_var(env, argv[i]) != NULL)
			del_var(&env, argv[i]);
	}
	return (0);
}
