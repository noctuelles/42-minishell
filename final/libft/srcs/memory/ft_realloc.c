/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:18:55 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/23 10:08:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	void	*newptr;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		newptr = malloc(newsize);
		if (!newptr)
			return (NULL);
		if (ptr && oldsize)
			ft_memcpy(newptr, ptr, oldsize);
	}
	return (newptr);
}
