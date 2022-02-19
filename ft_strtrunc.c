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


typedef unsigned int t_index;

#include <stddef.h>

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

/* ft_strtrunc() truncate the string pointed by str, by returning each
 * individual substring truncited by trunc.
 *
 * If the string pointed by str is empty, it returns NULL.
 * If the string pointed by str contains only trunc, it returns NULL.
 * If the string hasn't any substring left, it returns NULL.
 * Else, it returns a pointer to the beginning of a substring.
 *
 * Every quote at a beginning of a substring is dismiss : it will not be 
 * sensitive to any trunc character found within the substring.
 *
 * Exemple:
 *           
 *           char *str = strdup("This is \"an example\"");
 *
 * If we call ft_strtrunc() in a while loop, and printing str in the loop, it
 * not print :
 * 
 *           This
 *           is
 *           "an
 *           example"
 *
 * But instead :
 *
 *           This
 *           is
 *           "an example"
 *
 * (This function was created during minishell project).
 */

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

#include <stdio.h>

int main(int argc, char **argv)
{
	while (ft_strtrunc(&argv[1], ' '))
		puts(argv[1]);
}
