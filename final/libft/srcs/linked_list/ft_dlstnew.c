/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:43:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 00:55:08 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*dlist;

	dlist = (t_dlist *) malloc(sizeof(t_dlist));
	if (!dlist)
		return (NULL);
	dlist->content = content;
	dlist->prev = NULL;
	dlist->next = NULL;
	return (dlist);
}
