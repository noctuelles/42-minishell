/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:00:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 19:15:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_var	*update_var(t_dlist *lst_var, char *name, t_var to_update)
{
	t_var		*var;

	while (lst_var)
	{
		var = (t_var *) lst_var->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			*var = to_update;
			return (var);
		}
		lst_var = lst_var->next;
	}
	return (NULL);
}
