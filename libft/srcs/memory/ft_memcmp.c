/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:45:09 by paul              #+#    #+#             */
/*   Updated: 2021/11/25 17:16:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*b_s1;
	unsigned char	*b_s2;

	b_s1 = (unsigned char *)s1;
	b_s2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (--n && *b_s1 == *b_s2)
	{
		b_s1++;
		b_s2++;
	}
	return (*b_s1 - *b_s2);
}
