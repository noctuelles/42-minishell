/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_ret_last.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:19:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/27 17:23:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_back_ret_last(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	last_elem = NULL;
	if (!lst)
		return (last_elem);
	if (!*lst)
		*lst = new;
	else
	{
		last_elem = *lst;
		last_elem = ft_lstlast(last_elem);
		last_elem->next = new;
	}
	return (last_elem);
}
