/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:26:13 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/25 18:31:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	slen;
	size_t	i;
	char	*str;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	str = (char *) malloc((slen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < slen)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
