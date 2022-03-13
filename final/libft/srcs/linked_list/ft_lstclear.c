/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:31:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/11 17:36:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursion(t_list *lst, void (*del)(void *))
{
	if (lst)
		recursion(lst->next, (*del));
	ft_lstdelone(lst, (*del));
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (!*lst)
		return ;
	recursion(*lst, (*del));
	*lst = NULL;
}
