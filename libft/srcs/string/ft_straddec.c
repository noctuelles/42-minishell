/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:57:05 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/11 17:17:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_straddec(char **s, char c, size_t n)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s || !*s)
		return (NULL);
	if (n == 0)
		return (*s);
	i = 0;
	j = 0;
	str = (char *) malloc((ft_strlen(*s) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while ((*s)[j] != '\0')
		str[i++] = (*s)[j++];
	while (n--)
		str[i++] = c;
	str[i] = '\0';
	free(*s);
	*s = str;
	return (str);
}
