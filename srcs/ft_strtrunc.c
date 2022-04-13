/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:05:11 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/19 20:21:50 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

typedef unsigned int	t_index;

static inline t_index	jmp_quote(const char *str, t_index i, const char quote)
{
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (i);
}

static inline char	*jmp_delim(char *str, const char trunc)
{
	t_index	i;

	i = 0;
	while (str[i] == trunc)
		i++;
	return (&str[i]);
}

static inline char	*end_trunc(char **str, char **w_str)
{
	*str = *w_str;
	*w_str = NULL;
	return (NULL);
}

static inline char	*do_trunc(char **str, char **w_str, t_index i,
											const char trunc)
{
	while ((*w_str)[i] != '\0' && (*w_str)[i] != trunc)
		i++;
	*str = (*w_str);
	if ((*w_str)[i] != '\0')
	{
		(*w_str)[i] = '\0';
		*w_str = &(*w_str)[i + 1];
	}
	else
		*w_str = &(*w_str)[i];
	return (*str);
}

char	*ft_strtrunc(char **str, const char delim)
{
	static char	*w_str;
	t_index		i;


	if (!w_str)
		w_str = *str;
	i = 0;
	if (w_str[0] == '\0')
		return (end_trunc(str, &w_str));
	else if (w_str[0] == '\"' || w_str[0] == '\'')
		i = jmp_quote(w_str, i + 1, w_str[0]);
	else if (w_str[0] == delim)
	{
		w_str = jmp_delim(w_str, delim);
		if (w_str[0] == '\0')
			return (end_trunc(str, &w_str));
	}
	return (do_trunc(str, &w_str, i, delim));
}
