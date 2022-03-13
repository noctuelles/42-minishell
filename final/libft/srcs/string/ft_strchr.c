/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:43:56 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/01 16:19:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	if (c == '\0')
		return ((char *) &s[slen]);
	i = 0;
	while (i < slen)
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}
