/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:23:29 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/06 17:27:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static void	recursion(uint64_t n, const char *base,
													size_t baselen, int fd)
{
	if (n >= baselen)
		recursion(n / baselen, base, baselen, fd);
	ft_putchar_fd(base[n % baselen], fd);
}

void	ft_putnbr_base_fd(int64_t n, const char *base, int fd)
{
	size_t	baselen;

	baselen = get_baselen(base);
	if (!baselen)
		return ;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		recursion((uint64_t) - n, base, baselen, fd);
	}
	else
		recursion(n, base, baselen, fd);
}
