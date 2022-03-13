/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:28:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 12:30:19 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dlstdelone(t_dlist **lst, t_dlist *elem, void (*del)(void *))
{
	if (!elem || !(*lst))
		return ;
	if (elem->prev == NULL)
	{
		if (elem->next != NULL)
		{
			elem->next->prev = NULL;
			*lst = elem->next;
		}
		else
			*lst = NULL;
	}
	else if (elem->next == NULL)
		elem->prev->next = NULL;
	else
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	del(elem->content);
	free(elem);
}
