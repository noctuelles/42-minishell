/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:59:34 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 10:59:07 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int	ft_env(int argc, char **argv, t_minishell *minishell)
{
	t_dlist	*env;

	(void)argc;
	(void)argv;
	env = minishell->vars;
	while (env != NULL)
	{
		ft_printf("%s=%s\n", ((t_var *)env->content)->name,
			((t_var *)env->content)->value);
		env = env->next;
	}
	return (1);
}
