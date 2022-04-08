/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:30:25 by paul              #+#    #+#             */
/*   Updated: 2021/11/25 13:14:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*b_s;

	b_s = (unsigned char *)s;
	while (n--)
	{
		if (*b_s == (unsigned char)c)
			return (b_s);
		b_s++;
	}
	return (NULL);
}
