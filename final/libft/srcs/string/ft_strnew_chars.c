/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:19:36 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/09 16:23:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdarg.h>

char	*ft_strnew_chars(size_t n, ...)
{
	char	*str;
	size_t	i;
	va_list	va;

	str = (char *) malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	va_start(va, n);
	while (i < n)
		str[i++] = (unsigned char) va_arg(va, int);
	str[i] = '\0';
	va_end(va);
	return (str);
}
