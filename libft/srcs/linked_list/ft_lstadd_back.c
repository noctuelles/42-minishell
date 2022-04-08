/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:30:42 by plouvel           #+#    #+#             */
/*   Updated: 2021/11/26 16:05:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_elem = *lst;
		last_elem = ft_lstlast(last_elem);
		last_elem->next = new;
	}
}
