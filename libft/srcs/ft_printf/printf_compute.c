/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:02:37 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 01:01:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_compute_precision_add(t_printf_info *info)
{
	if (info->conv == 's')
		info->prcs_add = info->precision;
	else if (info->bufs.m_len <= info->precision)
	{
		info->prcs_add = info->precision - info->bufs.m_len;
		if (info->flags & NEG)
			info->prcs_add++;
	}
	else
		info->prcs_add = 0;
}

void	printf_compute_padding_len(t_printf_info *info)
{
	if (info->conv == 'c' && info->bufs.main[0] == '\0')
	{
		if (info->width > 0)
			info->pad_add = info->width - 1;
	}
	else if (info->bufs.m_len <= info->width)
		info->pad_add = info->width - info->bufs.m_len;
	else
		info->pad_add = 0;
}
