/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:05:15 by paul              #+#    #+#             */
/*   Updated: 2021/11/25 19:07:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*org;

	if (!dest && !src)
		return (NULL);
	org = dest;
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (org);
}
