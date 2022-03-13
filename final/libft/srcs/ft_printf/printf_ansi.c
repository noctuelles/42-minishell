/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ansi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:06:22 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 13:01:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static size_t	check_ansi_suite(const char *s)
{
	size_t	i;
	size_t	ndigits;

	i = 0;
	ndigits = 0;
	while (s[i] != '\0' && s[i] != '}')
	{
		if (ft_isdigit(s[i]) && ndigits < 3)
			ndigits++;
		else if (s[i] == ';')
			ndigits = 0;
		else
			return (0);
		i++;
	}
	return (i);
}

static char	*new_ansi_code(const char *suite, size_t len)
{
	char	*str;

	str = (char *) ft_calloc((3 + len + 1), sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\x1b';
	str[1] = '[';
	ft_strncat(str, suite, len);
	str[3 + (len - 1)] = 'm';
	str[3 + len] = '\0';
	return (str);
}

const char	*printf_putansi(const char *ansi, t_printf_info *info)
{
	char	*ansi_out;
	size_t	len;
	size_t	i;

	len = check_ansi_suite(ansi + 1);
	i = 0;
	if (!len)
	{
		while (ansi[i] != '\0')
		{
			printf_putchar(ansi[i], info);
			if (ansi[i] == '}')
				break ;
			i++;
		}
		return (&ansi[i]);
	}
	ansi_out = new_ansi_code(ansi + 1, len);
	if (!ansi_out)
		return (NULL);
	ft_putstr(ansi_out);
	free(ansi_out);
	return (&ansi[len + 1]);
}
