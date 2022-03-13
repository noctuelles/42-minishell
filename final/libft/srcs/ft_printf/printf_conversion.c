/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:46:39 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 13:34:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_pointer_conversion(void *p, t_printf_info *info)
{
	if (!p)
		info->bufs.main = ft_strdup(PTR_NULL);
	else
	{
		info->bufs.main = ft_itoa_ubase((uint64_t) p, HEX_LOWERCASE);
		ft_straddbs(&info->bufs.main, "0x");
	}
}

static void	printf_string_conversion(const char *s, t_printf_info *info)
{
	if (!s)
	{
		info->flags |= NULL_STR;
		info->bufs.main = ft_strdup(STR_NULL);
	}
	else
		info->bufs.main = ft_strdup(s);
}

int	printf_conversion(char spec, va_list ap, t_printf_info *info)
{
	if (spec == 'c')
		info->bufs.main = ft_strnew_chars(1, va_arg(ap, int));
	else if (spec == 's')
		printf_string_conversion(va_arg(ap, const char *), info);
	else if (spec == 'p')
		printf_pointer_conversion(va_arg(ap, void *), info);
	else if (spec == 'd' || spec == 'i')
		info->bufs.main = ft_itoa_base(va_arg(ap, int), DECIMAL);
	else if (spec == 'u')
		info->bufs.main = ft_itoa_base(va_arg(ap, unsigned int), DECIMAL);
	else if (spec == 'x')
		info->bufs.main = ft_itoa_base(va_arg(ap, unsigned int), HEX_LOWERCASE);
	else if (spec == 'X')
		info->bufs.main = ft_itoa_base(va_arg(ap, unsigned int), HEX_UPPERCASE);
	else if (spec == '%')
	{
		info->bufs.main = ft_strnew_chars(1, '%');
		info->flags |= PERCENT;
	}
	if (!info->bufs.main)
		return (0);
	return (1);
}
