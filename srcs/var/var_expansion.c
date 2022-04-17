/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:34:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/17 14:57:24 by dhubleur         ###   ########.fr       */
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

static void	*print_errmsg(void)
{
	ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
	return (NULL);
}

t_dlist	*var_expansion(t_dlist **args, t_dlist *elem,
		t_arg *arg, t_dlist *env_var)
{
	ssize_t	i;
	t_dlist	*subargs;

	i = 0;
	while (arg->value[i] != '\0')
	{
		if (arg->value[i] == SQUOTE || arg->value[i] == DQUOTE)
			update_quote(&arg->value[i], &arg->quote);
		else if (arg->quote != SQUOTE && arg->value[i] == '$')
		{
			i = include_variable(arg, get_var_info(&arg->value[i + 1],
					env_var));
			if (i == -2)
				return (print_errmsg());
		}
		i++;
	}
	subargs = post_process(args, elem, arg);
	if (subargs == NULL && errno != ENO)
		return (print_errmsg());
	else
		return (subargs);
}
