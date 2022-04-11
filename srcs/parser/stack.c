/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:12:13 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/11 17:27:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

t_dlist	*push_stack(t_parse_stack *stack, void *content)
{
	t_dlist	*elem;

	elem = ft_dlstnew(content);
	if (!elem)
		return (NULL);
	ft_dlstadd_back(&stack->cnt, elem);
	stack->top = elem;
	return (elem);
}

void	pop_stack(t_parse_stack *stack, void (*del)(void *))
{
	t_dlist	*top_prev;

	top_prev = stack->cnt->prev;
	ft_dlstdelone(&stack->cnt, stack->top, del);
	stack->top = top_prev;
}

t_token_type	*new_token_type(t_token_type type)
{
	t_token_type	*tkn_type;

	tkn_type = (t_token_type *) malloc(sizeof(t_token_type));
	if (!tkn_type)
		return (NULL);
	*tkn_type = type;
	return (tkn_type);
}
