/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:27:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 11:35:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*elem;
	t_dlist	*next;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	elem = *lst;
	while (elem)
	{
		next = elem->next;
		ft_dlstdelone(lst, elem, (*del));
		elem = next;
	}
}
