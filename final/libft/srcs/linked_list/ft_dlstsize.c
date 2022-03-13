/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:44:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 19:46:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dlstsize(t_dlist *lst)
{
	size_t		size;

	if (lst == NULL)
		return (0);
	size = 1;
	while (lst->next != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
