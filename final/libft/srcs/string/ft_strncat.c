/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:27:49 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 12:30:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t	i;
	char	*org;

	i = 0;
	org = dest;
	while (*dest)
		dest++;
	while (src[i] && i < nb)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (org);
}
