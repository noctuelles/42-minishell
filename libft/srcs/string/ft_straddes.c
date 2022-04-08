/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:34:36 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/09 13:51:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
 *	ft_straddes -> string add end string
 *	Add a string to the end of the string
 */

char	*ft_straddes(char **s, const char *add)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s || *s)
		return (NULL);
	if (!add)
		return (*s);
	str = (char *) malloc((ft_strlen(*s) + ft_strlen(add) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while ((*s)[j] != '\0')
		str[i++] = (*s)[j++];
	j = 0;
	while (add[j] != '\0')
		str[i++] = add[j++];
	str[i] = '\0';
	free(*s);
	*s = str;
	return (str);
}
