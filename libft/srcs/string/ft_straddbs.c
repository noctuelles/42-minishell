/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:33:52 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/09 17:27:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
 *	ft_straddbs -> string add beginning string
 *	Add a string to the beginning of the string
 */

char	*ft_straddbs(char **s, const char *add)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s || !*s)
		return (NULL);
	if (!add)
		return (*s);
	str = (char *) malloc((ft_strlen(*s) + ft_strlen(add) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (add[j] != '\0')
		str[i++] = add[j++];
	j = 0;
	while ((*s)[j] != '\0')
		str[i++] = (*s)[j++];
	str[i] = '\0';
	free(*s);
	*s = str;
	return (str);
}
