/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:08:10 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 16:08:21 by plouvel          ###   ########.fr       */
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

static t_dlist	*post_process(t_dlist **args, t_dlist *elem, t_arg *arg,
		t_minishell *minishell)
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
			return (set_minishell_err_null(minishell, ERR_MALLOC));
		if (ft_dlstsize(subtkns) > 1 && arg->type != ARG_WORD)
		{
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, "ambiguous redirect",
				arg->value);
			minishell->ambiguous_redir = true;
		}
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
				return (display_error_more(minishell, STR_MALLOC, ERR_MALLOC));
		}
		i++;
	}
	subargs = post_process(args, elem, arg, minishell);
	if (subargs == NULL && minishell->err)
		return (display_error_more(NULL, STR_MALLOC, 0));
	else
		return (subargs);
}
