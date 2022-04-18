/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:12:13 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 03:16:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

t_dlist	*push_stack(t_parser *parser, t_parse_stack *stack, void *content)
{
	t_dlist	*elem;

	elem = ft_dlstnew(content);
	if (!elem)
		return (set_parser_errcode(parser, ERR_MALLOC));
	ft_dlstadd_back(&stack->cnt, elem);
	stack->top = elem;
	return (elem);
}

void	pop_stack(t_parse_stack *stack, size_t times)
{
	t_dlist	*top_prev;
	size_t	i;

	if (!stack->top)
		return ;
	i = 0;
	while (i < times)
	{
		top_prev = stack->top->prev;
		ft_dlstdelone(&stack->cnt, stack->top, NULL);
		stack->top = top_prev;
		i++;
	}
}
