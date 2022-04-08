/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:23:10 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/29 18:01:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_nwords(const char *str, char delim, size_t *idx)
{
	int		in_word;
	size_t	nwords;
	size_t	i;

	in_word = 0;
	nwords = 0;
	i = 0;
	*idx = 0;
	while (str[i] != '\0')
	{
		if (!in_word)
		{
			if (str[i] != delim)
			{
				in_word = 1;
				nwords++;
			}
		}
		else
			if (str[i] == delim)
				in_word = 0;
		i++;
	}
	return (nwords);
}

static size_t	get_lword(const char *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != delim)
		i++;
	return (i);
}

static void	get_next_word(const char **str, char delim, size_t *idx)
{
	const char	*s;

	s = *str;
	*idx = 0;
	while (*s != '\0' && *s == delim)
		s++;
	*str = s;
}

/*
 *	If the malloc fails in the middle of the strs array, it must free
 *	precedent allocation.
 */

static char	**free_strs(char **strs, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	nwords;
	size_t	j;
	size_t	i;
	size_t	lword;

	if (!s)
		return (NULL);
	nwords = get_nwords(s, c, &i);
	strs = (char **) malloc((nwords + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (nwords--)
	{
		get_next_word(&s, c, &j);
		lword = get_lword(s, c);
		strs[i] = (char *) malloc ((lword + 1) * sizeof(char));
		if (!strs[i])
			return (free_strs(strs, i));
		while (j < lword)
			strs[i][j++] = *s++;
		strs[i++][j] = '\0';
	}
	strs[i] = NULL;
	return (strs);
}
