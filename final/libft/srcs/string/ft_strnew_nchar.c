/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_nchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:10:43 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/09 16:22:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew_nchar(char c, size_t n)
{
	char	*str;
	size_t	i;

	if (n == 0)
	{
		c = '\0';
		n = 1;
	}
	str = (char *) malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}
