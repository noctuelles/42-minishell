/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:19:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 14:20:58 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_pwd(int argc, char **argv, t_env **env)
{
	printf("%s\n", get_value(env, "PWD"));
}