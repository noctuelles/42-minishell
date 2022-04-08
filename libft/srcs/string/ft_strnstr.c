/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:42:08 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/25 17:49:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	If the needle is just on character, execute strchr instead.
 *	If the needle lenght is greater than the haystack, exit the program.
 *	
 *						### ALGORITHM ###
 *
 *	H e l l o   e v e r y b o d y , a r e   y o u   o k ?
 *
 *	We're searching: "r y b o d y"
 *	
 *	H e l l o   e v e r y b o d y , a r e   y o u   o k ?
 *	^         ^
 *	r y b o d y
 *
 *	H e l l o   e v e r y b o d y , a r e   y o u   o k ?
 *    ^         ^
 *    r y b o d y
 *
 *	ETC....
 *
 *	H e l l o   e v e r y b o d y , a r e   y o u   o k ?
 *	                  ^         ^
 *	                  r y b o d y
 *	It matches: now use strncmp on the inside. If suceeded, we return the
 *	pointer pointing to 'r', else, we continue our search.
 */

static char	*ft_strnchr(const char *s, int c, size_t len)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	if (slen == 0 && c == '\0')
		return ((char *) s);
	i = 0;
	while (i <= slen && len--)
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	haystack_len;
	size_t	needle_len;

	i = 0;
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 1 && len != 0)
		return (ft_strnchr(haystack, *needle, len));
	if (needle_len == 0)
		return ((char *) haystack);
	if (needle_len <= haystack_len)
	{
		while (i < len && haystack[i] != '\0' && i <= haystack_len - needle_len)
		{
			if (haystack[i] == needle[0]
				&& haystack[i + needle_len - 1] == needle[needle_len - 1])
				if (ft_strncmp(&haystack[i + 1], needle + 1,
						needle_len - 2) == 0 && len >= i + needle_len)
					return ((char *) &haystack[i]);
			i++;
		}
	}
	return (NULL);
}
