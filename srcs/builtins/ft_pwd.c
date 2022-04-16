/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:19:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:27:04 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(int argc, char **argv, t_dlist *env)
{
	(void)argc;
	(void)argv;
	printf("%s\n", get_var(env, "PWD")->value);
	return (0);
}
