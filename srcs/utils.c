/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:22:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 12:23:08 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	*set_minishell_err_null(t_minishell *minishell, int err)
{
	minishell->err = err;
	return (NULL);
}
