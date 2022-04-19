/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:19:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 12:09:56 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int	ft_pwd(int argc, char **argv, t_minishell *minishell)
{
	(void)argc;
	(void)argv;
	if (get_var(minishell->vars, "PWD") != NULL)
		ft_printf("%s\n", get_var(minishell->vars, "PWD")->value);
	else
		ft_printf("minishell: unable to locate current directory\n");
	return (0);
}
