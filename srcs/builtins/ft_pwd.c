/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:19:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 10:59:13 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int	ft_pwd(int argc, char **argv, t_minishell *minishell)
{
	(void)argc;
	(void)argv;
	ft_printf("%s\n", get_var(minishell->vars, "PWD")->value);
	return (0);
}
