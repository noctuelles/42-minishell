/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:19:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/07 11:56:48 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_pwd(int argc, char **argv, t_dlist *env)
{
	(void)argc;
	(void)argv;
	printf("%s\n", get_var(env, "PWD")->value);
	return (0);
}
