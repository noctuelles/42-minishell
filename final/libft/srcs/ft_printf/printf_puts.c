/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_puts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:17:20 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 13:08:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	printf_putchar(char c, t_printf_info *info)
{
	ft_putchar(c);
	info->wlen++;
}

void	printf_putstr(const char *str, t_printf_info *info)
{
	size_t	len;

	len = ft_strlen(str);
	write(1, str, len);
	info->wlen += len;
}

void	printf_put_buffers(t_printf_info *info)
{
	if (info->bufs.left)
		printf_putstr(info->bufs.left, info);
	if (info->bufs.main)
	{
		if (info->conv == 'c' && info->bufs.main[0] == '\0')
			printf_putchar('\0', info);
		else
			printf_putstr(info->bufs.main, info);
	}
	if (info->bufs.right)
		printf_putstr(info->bufs.right, info);
	free(info->bufs.left);
	free(info->bufs.main);
	free(info->bufs.right);
}

/*
void	print_infos(t_printf_info info)
{
	puts("\n-- printf info structure --\n");
	puts("## BUFFERS ##\n");
	printf(	"\tleft:\t\"%s\"\n"
			"\tmain:\t\"%s\"\n"
			"\tright:\t\"%s\"\n"
			"\tm_len:\t%ld\n\n",
			info.bufs.left,
			info.bufs.main,
			info.bufs.right,
			info.bufs.m_len);
	puts("## PRCS AND PADDING ##\n");
	printf(	"\tprecision_add:\t%ld\n"
			"\tpadding_add:\t%ld\n\n",
			info.precision_add,
			info.padding_add);
	puts("## GENERAL ##\n");
	printf(	"\tconversion:\t'%c'\n",
			info.conversion);
	ft_putstr_fd("\tflags:\t\t", 1);
	ft_putbin_fd(info.flags, 8, 1);
	printf(	"\n\twidth:\t\t%ld\n"
			"\tprecision:\t%ld\n\n",
			info.width,
			info.precision);
}*/
