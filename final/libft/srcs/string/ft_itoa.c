/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:31:03 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/07 12:22:13 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_nchar(int n)
{
	size_t			size;
	unsigned int	i;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		i = (unsigned int) - n;
	}
	else
		i = n;
	while (i != 0)
	{
		size++;
		i /= 10;
	}
	return (size);
}

static void	fillstr(char *str, const char *base, unsigned int n)
{
	if (n > 9)
		fillstr(str - 1, base, n / 10);
	*str = base[n % 10];
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	nchar;

	nchar = get_nchar(n);
	str = (char *) malloc((nchar + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		fillstr(&str[nchar - 1], "0123456789", (unsigned int) -n);
	}
	else
		fillstr(&str[nchar - 1], "0123456789", n);
	str[nchar] = '\0';
	return (str);
}
