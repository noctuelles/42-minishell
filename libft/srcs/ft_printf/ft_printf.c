/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:34:48 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 12:54:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	t_printf_info	info;

	va_start(ap, format);
	info.wlen = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			printf_flush_info(&info);
			format = printf_parse(format + 1, ap, &info);
			if (!format)
				return (-1);
			printf_flags_compute_n_apply(&info);
			printf_put_buffers(&info);
		}
		else if (*format == '{')
			format = printf_putansi(format, &info);
		else
			printf_putchar(*format, &info);
		format++;
	}
	va_end(ap);
	return (info.wlen);
}
