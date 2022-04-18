/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:20:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 18:02:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

static t_arg_type	cast_token_type(t_token_type token_type)
{
	t_arg_type	arg_type;

	arg_type = ARG_WORD;
	if (token_type == T_GRT)
		arg_type = ARG_REDIRECT_FILE;
	else if (token_type == T_LESS)
		arg_type = ARG_REDIRECT_STDIN;
	else if (token_type == T_DGRT)
		arg_type = ARG_REDIRECT_FILE_APPEND;
	else if (token_type == T_DLESS)
		arg_type = ARG_REDIRECT_HERE_DOC;
	return (arg_type);
}

t_arg	*new_arg(char *value, t_token_type token_type, bool dup)
{
	t_arg		*arg;
	char		*arg_value;
	t_arg_type	arg_type;

	arg_type = cast_token_type(token_type);
	arg = (t_arg *) ft_calloc(1, sizeof(t_arg));
	if (!arg)
		return (NULL);
	if (dup)
		arg_value = ft_strdup(value);
	else
		arg_value = value;
	if (!arg_value)
	{
		free(arg);
		return (NULL);
	}
	arg->quote = '\0';
	arg->type = arg_type;
	arg->value = arg_value;
	return (arg);
}

void	free_arg(void *parg)
{
	t_arg	*arg;

	arg = (t_arg *) parg;
	if (arg->quote_lst)
		ft_lstclear(&arg->quote_lst, NULL);
	if (arg->rem_quote_lst)
		ft_lstclear(&arg->rem_quote_lst, NULL);
	if (arg->wldc_lst)
		ft_lstclear(&arg->wldc_lst, NULL);
	free(arg->value);
	free(arg);
}

t_arg	*add_arg_to_list(t_parser *parser, t_dlist **args, t_token_type type)
{
	t_arg	*arg;
	t_dlist	*elem;

	arg = new_arg(parser->curr_tkn->val, type, true);
	if (!arg)
		return (NULL);
	elem = ft_dlstnew(arg);
	if (!elem)
	{
		free_arg(arg);
		return (NULL);
	}
	ft_dlstadd_back(args, elem);
	consume_token(parser);
	return (arg);
}
