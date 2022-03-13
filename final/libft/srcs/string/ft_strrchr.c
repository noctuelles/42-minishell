/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:34:12 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/01 16:18:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Return the last occurance of c in the string s.
 *	<-> Start the search at the end of the string.
 *
 *	"C e c i   e s t   c a c a   c o c o"
 *	                                 ^
 *	                                 |
 *	                             occurence
 */

char	*ft_strrchr(const char *s, int c)
{
	int	slen;

	slen = ft_strlen(s);
	while (slen >= 0)
	{
		if (s[slen] == (unsigned char) c)
			return ((char *) &s[slen]);
		slen--;
	}
	return (NULL);
}
