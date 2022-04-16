/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:56:39 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/16 17:06:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdlib.h>

t_list	*add_to_list(t_list **list, void *content)
{
	t_list	*elem;

	elem = ft_lstnew(content);
	if (!elem)
		return (NULL);
	ft_lstadd_back(list, elem);
	return (elem);
}

bool	is_expnd_quote(t_list *lst, char *pquote)
{
	while (lst != NULL)
	{
		if ((char *) lst->content == pquote)
			return (true);
		lst = lst->next;
	}
	return (false);
}

bool	is_rem_quote(t_list *lst, char *pquote)
{
	while (lst != NULL)
	{
		if ((char *) lst->content == pquote)
			return (true);
		lst = lst->next;
	}
	return (false);
}

t_list	*is_intrp_wldc(t_list *lst, char *c)
{
	while (lst != NULL)
	{
		if ((char *) lst->content == c)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_dlist	*insert_list(t_dlist **main_lst, t_dlist *to_insert, t_dlist *elem)
{
	t_dlist	*lst_last;

	if (!to_insert)
		return (elem);
	lst_last = ft_dlstlast(to_insert);
	if (elem->prev)
	{
		elem->prev->next = to_insert;
		to_insert->prev = elem->prev;
	}
	else
		*main_lst = to_insert;
	if (elem->next)
	{
		elem->next->prev = lst_last;
		lst_last->next = elem->next;
	}
	free_arg(elem->content);
	free(elem);
	return (lst_last);
}
