/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:38:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:32:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include <stdlib.h>

void	create_new_string(char *str, char *new_str, int size, int length)
{
	while (str[++size])
	{
		if (str[size] == '"' || str[size] == '\\' || str[size] == '$')
			new_str[length++] = '\\';
		new_str[length++] = str[size];
	}
	new_str[length] = '\0';
}

void	print_string_escape_quote(char *str)
{
	int		size;
	int		length;
	char	*new_str;

	size = -1;
	length = 0;
	while (str[++size])
	{
		length++;
		if (str[size] == '"' || str[size] == '\\' || str[size] == '$')
			length++;
	}
	new_str = malloc(sizeof(char) * (length + 1));
	if (!new_str)
		exit(1);
	size = -1;
	length = 0;
	create_new_string(str, new_str, size, length);
	ft_printf("%s", new_str);
	free(new_str);
}

t_dlist	*print_var(t_dlist *env)
{
	ft_printf(EXPORT_LIST, ((t_var *)env->content)->name);
	print_string_escape_quote(((t_var *)env->content)->value);
	ft_printf("\"\n");
	return (env->next);
}

int	ft_export(int argc, char **argv, t_minishell *minishell)
{
	int		i;
	t_dlist	*env;

	env = minishell->vars;
	if (argc < 2)
	{
		while (env != NULL)
			env = print_var(env);
		return (0);
	}
	i = 0;
	while (++i < argc)
	{
		if (ft_strchr(argv[i], '='))
			import_one_var(&env, argv[i]);
		else
		{
			if (get_var(env, argv[i]) == NULL)
				add_var(&env, argv[i], "");
		}
	}
	return (0);
}
