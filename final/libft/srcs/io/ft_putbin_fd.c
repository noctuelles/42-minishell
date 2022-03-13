/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbin_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 13:24:46 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/06 13:41:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbin_fd(int64_t n, size_t nbits, int fd)
{
	size_t	i;

	i = 0;
	while (i < nbits)
	{
		if (n & ((1U << (nbits - 1)) >> i))
			ft_putchar_fd('1', fd);
		else
			ft_putchar_fd('0', fd);
		i++;
	}
}
