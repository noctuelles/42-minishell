/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:04:34 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/25 18:29:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	only_charset(const char *str, const char *set)
{
	while (*str != '\0')
		if (!is_in_set(*str++, set))
			return (0);
	return (1);
}

/*
 *	If str is empty or only contains char from the charset, it set both
 *	beginning and end to NULL.
 *	This function set the boundaries of a string by setting two pointer on
 *	char.
 */

static void	get_boundaries(char const *str, const char *set,
												char **beginning, char **end)
{
	if (only_charset(str, set) || ft_strlen(str) == 0)
	{
		*beginning = NULL;
		*end = NULL;
		return ;
	}
	while (is_in_set(*str, set))
		str++;
	*beginning = (char *) str;
	while (*str != '\0')
		str++;
	str--;
	while (is_in_set(*str, set))
		str--;
	*end = (char *) str;
}

/*
 *	This function copy the string within bondaries.
 */

static char	*strcpy_wbnd(char *dest, const char *beginning, const char *end)
{
	size_t	i;

	i = 0;
	while (beginning <= end)
		dest[i++] = *beginning++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	str_size;
	char	*beginning;
	char	*end;

	if (!s1)
		return (NULL);
	get_boundaries(s1, set, &beginning, &end);
	if (beginning == NULL && end == NULL)
		str_size = 1;
	else
		str_size = end - beginning + 2;
	str = (char *) malloc(str_size * sizeof(char));
	if (!str)
		return (NULL);
	if (str_size == 1)
		*str = '\0';
	else
		strcpy_wbnd(str, beginning, end);
	return (str);
}
