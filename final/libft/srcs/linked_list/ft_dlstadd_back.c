/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:46:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/17 13:41:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*elem;

	if (!dlst)
		return ;
	if (!*dlst)
	{
		*dlst = new;
	}
	else
	{
		elem = *dlst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
		new->prev = elem;
	}
}
