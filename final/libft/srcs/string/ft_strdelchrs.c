/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:46:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 15:01:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static inline void	shift_str(char *str, unsigned char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] == c)
			shift_str(&str[i + 1], c);
		str[i] = str[i + 1];
		i++;
	}
}

char	*ft_strdelchrs(char *str, const char *charset)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (charset[j] != '\0')
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == (unsigned char) charset[j])
				shift_str(&str[i], (unsigned char) charset[j]);
			i++;
		}
		j++;
	}
	return (str);
}
