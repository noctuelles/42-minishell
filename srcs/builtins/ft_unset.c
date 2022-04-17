/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:05:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/17 14:24:43 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(int argc, char **argv, t_minishell *minishell)
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
		if (get_var(minishell->vars, argv[i]) != NULL)
			del_var(&(minishell->vars), argv[i]);
	}
	return (0);
}
