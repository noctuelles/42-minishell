/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:59:34 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/07 11:50:37 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, char **argv, t_dlist *env)
{
	(void)argc;
	(void)argv;
	while (env != NULL)
	{
		printf("%s=%s\n", ((t_var *)env->content)->name,
			((t_var *)env->content)->value);
		env = env->next;
	}
	return (1);
}