/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:46:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 17:48:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*elem;

	if (!dlst)
		return ;
	if (!*dlst)
		*dlst = new;
	else
	{
		elem = *dlst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
		new->prev = elem;
	}
}
