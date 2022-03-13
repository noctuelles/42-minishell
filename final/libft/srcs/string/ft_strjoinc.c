/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:41:25 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/08 13:34:36 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinc(const char *s1, const char *s2, char c)
{
	char	*str;
	size_t	strlen;
	size_t	i;

	i = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (*s1 != '\0')
	{
		str[i] = *s1;
		if (*s1 == c)
			break ;
	}
	while (*s2 != '\0')
		str[i] = *s2++;
	while (*s1 != '\0')
		str[i] = *s1++;
	str[i] = '\0';
	return (str);
}
