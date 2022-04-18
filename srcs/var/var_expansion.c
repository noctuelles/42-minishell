/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2022/04/17 22:08:13 by dhubleur         ###   ########.fr       */
/*   Updated: 2022/04/18 14:38:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

static void	update_quote(char *str, char *quote)
{
	if (*quote == '\0')
		*quote = *str;
	else if (*str == *quote)
		*quote = '\0';
}

static t_dlist	*post_process(t_dlist **args, t_dlist *elem, t_arg *arg)
{
	t_dlist	*next;
	t_dlist	*subtkns;

	if (arg->value[0] == '\0')
	{
		next = elem->next;
		ft_dlstdelone(args, elem, free_arg);
		return (next);
	}
	else
	{
		subtkns = tokenize_from_arg(arg, arg->value);
		if (subtkns == NULL)
			return (NULL);
		return (insert_list(args, subtkns, elem));
	}
}

t_dlist	*var_expansion(t_dlist **args, t_dlist *elem,
		t_arg *arg, t_minishell *minishell)
{
	ssize_t	i;
	t_dlist	*subargs;

	i = 0;
	if (arg->value[0] == '$' && arg->value[1] == '\0')
		return (elem);
	while (arg->value[i] != '\0')
	{
		if (arg->value[i] == SQUOTE || arg->value[i] == DQUOTE)
			update_quote(&arg->value[i], &arg->quote);
		else if (arg->quote != SQUOTE && arg->value[i] == '$')
		{
			i = include_variable(arg, get_var_info(&arg->value[i + 1],
						minishell));
			if (i == -2)
				return (display_error_more(STR_MALLOC));
		}
		i++;
	}
	subargs = post_process(args, elem, arg);
	if (subargs == NULL && errno != ENO)
		return (display_error_more(STR_MALLOC));
	else
		return (subargs);
}
