/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:06:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 15:40:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "builtins.h"
#include "minishell.h"
#include "signals.h"
#include <readline/readline.h>

static char	*build_prompt_prefix(const char *user, const char *pwd)
{
	char	*prompt;
	size_t	user_len;
	size_t	pwd_len;

	user_len = ft_strlen(user);
	pwd_len = ft_strlen(pwd);
	prompt = malloc((user_len + pwd_len + 5) * sizeof(char));
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strcat(prompt, user);
	prompt[user_len - 1] = '@';
	ft_strcat(prompt, pwd);
	ft_strcat(prompt, STR_PROMPT_ARROW);
	return (prompt);
}

static char	*prompt_and_read(t_dlist *vars)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	char	*str;

	if (get_var(vars, "PWD") == NULL || get_var(vars, "USER") == NULL)
		return (readline(STR_STD_PROMPT));
	user = get_var(vars, "USER")->value;
	pwd = get_var(vars, "PWD")->value;
	prompt = build_prompt_prefix(user, pwd);
	if (!prompt)
		return (NULL);
	str = readline(prompt);
	free(prompt);
	return (str);
}

char	*read_from_user(t_minishell *minishell)
{
	char	*str;
	char	*pnw;

	set_signals_as_prompt();
	if (refill_env(&minishell->vars) != 0)
		ft_exit(1, NULL, minishell);
	if (isatty(STDIN_FILENO) == 1)
		str = prompt_and_read(minishell->vars);
	else
	{
		str = get_next_line(STDIN_FILENO);
		if (str)
		{
			pnw = ft_strchr(str, '\n');
			if (pnw)
				*pnw = '\0';
		}
	}
	if (str == NULL)
		ft_exit(1, NULL, minishell);
	return (str);
}
