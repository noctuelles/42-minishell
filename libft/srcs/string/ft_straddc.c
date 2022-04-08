/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:50:53 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/11 17:20:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_straddc(char **s, char stop, char c, size_t n)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s || !*s || stop == '\0' || n == 0)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *) malloc((ft_strlen(*s) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while ((*s)[j] != '\0')
	{
		str[i++] = (*s)[j];
		if ((*s)[j++] == stop)
			break ;
	}
	while (n--)
		str[i++] = c;
	while ((*s)[j] != '\0')
		str[i++] = (*s)[j++];
	str[i] = '\0';
	free(*s);
	*s = str;
	return (str);
}
