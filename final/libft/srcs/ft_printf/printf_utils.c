/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:27:40 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 18:45:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	printf_is_valid_flag(char c)
{
	if (ft_strchr(FLAGS, c))
		return (TRUE);
	return (FALSE);
}

t_bool	printf_is_nbr_conv(t_printf_info *info)
{
	if (info->conv == 'd' || info->conv == 'i' || info->conv == 'u'
		|| info->conv == 'x' || info->conv == 'X')
		return (TRUE);
	else
		return (FALSE);
}

void	printf_flush_info(t_printf_info *info)
{
	info->bufs.right = NULL;
	info->bufs.main = NULL;
	info->bufs.m_len = 0;
	info->bufs.left = NULL;
	info->conv = 0;
	info->prcs_add = 0;
	info->pad_add = 0;
	info->flags = NO_FLAGS;
	info->width = 0;
	info->precision = 0;
}

void	printf_update_mlen(t_printf_info *info)
{
	info->bufs.m_len = ft_strlen(info->bufs.main);
}
