/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:34:05 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/25 11:26:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	offset;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	offset = dest_len;
	if (size > 0 && dest_len < size)
	{
		while (*src != '\0' && offset < size - 1)
			dest[offset++] = *src++;
		dest[offset] = '\0';
		return (src_len + dest_len);
	}
	return (src_len + size);
}
