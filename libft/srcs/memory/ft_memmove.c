/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:29:17 by paul              #+#    #+#             */
/*   Updated: 2021/11/25 19:06:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Modern implementation of memcpy safely handle memory overlap.
 *	In seems that it do a plain memmove in such case.
 *	is_overlapping check if the memory zone doesn't overlap.
 *
 *	L e a r n i n g i s f u n
 */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*b_dest;
	unsigned char	*b_src;

	if (!dest && !src)
		return (NULL);
	b_dest = (unsigned char *)dest;
	b_src = (unsigned char *)src;
	if (b_dest <= b_src)
		ft_memcpy(dest, src, n);
	else
	{
		b_src += n - 1;
		b_dest += n - 1;
		while (n--)
			*b_dest-- = *b_src--;
	}
	return (dest);
}
