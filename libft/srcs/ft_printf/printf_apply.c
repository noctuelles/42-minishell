/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:03:42 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 18:42:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_invalidate(t_printf_info *info)
{
	info->bufs.main[0] = '\0';
	info->bufs.m_len = 0;
}

/*
 *	The printf_invalidate for the NULL_STR might be useless.
 *	To be compare on other machine.
 */

static void	printf_apply_precision(t_printf_info *info)
{
	if (info->flags & NULL_STR && info->precision < (sizeof(STR_NULL) - 1))
		return (printf_invalidate(info));
	if (info->conv == 'd' || info->conv == 'i' || info->conv == 'u')
	{
		if (info->flags & NEG)
			ft_straddc(&info->bufs.main, '-', '0', info->prcs_add);
		else if (info->flags & SIGN)
			ft_straddc(&info->bufs.main, '+', '0', info->prcs_add);
		else if (info->flags & SPACE)
			ft_straddc(&info->bufs.main, ' ', '0', info->prcs_add);
		else
			ft_straddbc(&info->bufs.main, '0', info->prcs_add);
	}
	else if (info->conv == 'x' || info->conv == 'X')
	{
		if (info->flags & AF)
			ft_straddc(&info->bufs.main, info->conv, '0', info->prcs_add);
		else
			ft_straddbc(&info->bufs.main, '0', info->prcs_add);
	}
	else if (info->conv == 's' && info->prcs_add <= info->bufs.m_len)
		info->bufs.main[info->prcs_add] = '\0';
	printf_update_mlen(info);
}

static void	printf_apply_padding(t_printf_info *info)
{
	if (info->flags & ZERO_PAD)
	{
		if (info->conv == 'd' || info->conv == 'i' || info->conv == 'u')
		{
			if (info->flags & NEG)
				ft_straddc(&info->bufs.main, '-', '0', info->pad_add);
			else if (info->flags & SIGN)
				ft_straddc(&info->bufs.main, '+', '0', info->pad_add);
			else if (info->flags & SPACE)
				ft_straddc(&info->bufs.main, ' ', '0', info->pad_add);
			else
				info->bufs.left = ft_strnew_nchar('0', info->pad_add);
		}
		else if (info->conv == 'x' || info->conv == 'X')
		{
			if (info->flags & AF)
				ft_straddc(&info->bufs.main, info->conv, '0', info->pad_add);
			else
				ft_straddbc(&info->bufs.main, '0', info->pad_add);
		}
	}
	else if (info->flags & R_JUST)
		info->bufs.left = ft_strnew_nchar(' ', info->pad_add);
	else if (info->flags & L_JUST)
		info->bufs.right = ft_strnew_nchar(' ', info->pad_add);
}

static void	printf_apply_primary_flags(t_printf_info *info)
{
	if (info->conv == 'd' || info->conv == 'i')
	{
		if ((info->flags & SIGN) && !(info->flags & NEG))
			ft_straddbc(&info->bufs.main, '+', 1);
		else if ((info->flags & SPACE) && !(info->flags & NEG))
			ft_straddbc(&info->bufs.main, ' ', 1);
	}
	else if ((info->conv == 'x') && (info->flags & AF)
		&& !(info->flags & ZERO_VAL))
		ft_straddbs(&info->bufs.main, "0x");
	else if ((info->conv == 'X') && (info->flags & AF)
		&& !(info->flags & ZERO_VAL))
		ft_straddbs(&info->bufs.main, "0X");
	printf_update_mlen(info);
}

/*
 *	Compute the eventual precision.
 *	We apply the 'primary flags' : '#', '+', ' '.
 *	We apply the precision : '.' .
 *	Compute the eventual padding.
 *	Apply the paddings (all others flags : '-' and normal padding).
 */

void	printf_flags_compute_n_apply(t_printf_info *info)
{
	if (!(info->flags & PERCENT))
	{
		if (printf_is_nbr_conv(info) && info->flags & ZERO_VAL)
		{
			if (info->flags & PRCS && info->precision == 0)
			{
				printf_invalidate(info);
				info->flags ^= PRCS;
			}
		}
		if (info->flags & PRCS)
			printf_compute_precision_add(info);
		if (info->flags & SIGN || info->flags & SPACE || info->flags & AF)
			printf_apply_primary_flags(info);
		if (info->flags & PRCS)
			printf_apply_precision(info);
		if (info->flags & R_JUST || info->flags & L_JUST
			|| info->flags & ZERO_PAD)
		{
			printf_compute_padding_len(info);
			printf_apply_padding(info);
		}
	}
}
