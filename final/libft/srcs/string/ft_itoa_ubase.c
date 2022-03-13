/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ubase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:48:37 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/10 14:53:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_baselen(const char *base)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (base[i] != '\0')
	{
		j = 0;
		if (base[i] == '-' || base[i] == '+')
			return (0);
		while (j < i)
			if (base[j++] == base[i])
				return (0);
		i++;
	}
	if (i == 0 || i == 1)
		return (0);
	return (i);
}

static size_t	get_nchar(uint64_t n, size_t baselen)
{
	size_t		size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		size++;
		n /= baselen;
	}
	return (size);
}

static void	fillstr(char *str, const char *base, size_t baselen, uint64_t n)
{
	if (n >= baselen)
		fillstr(str - 1, base, baselen, n / baselen);
	*str = base[n % baselen];
}

char	*ft_itoa_ubase(uint64_t n, const char *base)
{
	char	*str;
	size_t	baselen;
	size_t	nchar;

	baselen = get_baselen(base);
	if (!baselen)
		return (NULL);
	nchar = get_nchar(n, baselen);
	str = (char *) malloc((nchar + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	fillstr(&str[nchar - 1], base, baselen, n);
	str[nchar] = '\0';
	return (str);
}
