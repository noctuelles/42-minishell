/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_nocnt_alloc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:35:32 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/11 17:36:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	recursion(t_list *lst)
{
	if (lst)
		recursion(lst->next);
	free(lst);
}

void	ft_lstclear_nocnt_alloc(t_list **lst)
{
	if (!lst)
		return ;
	if (!*lst)
		return ;
	recursion(*lst);
	*lst = NULL;
}
