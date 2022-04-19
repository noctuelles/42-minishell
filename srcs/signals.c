/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:19:31 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 16:27:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "execution.h"
#include "minishell.h"

int	g_sigint = 0;

int	set_signals_as_prompt(void)
{
	struct sigaction	as_prompt;

	as_prompt.sa_handler = signal_handler_as_prompt;
	sigemptyset(&as_prompt.sa_mask);
	as_prompt.sa_flags = 0;
	if (sigaction(SIGINT, &as_prompt, NULL) == -1
		|| sigaction(SIGQUIT, &as_prompt, NULL) == -1)
		return (-1);
	else
		return (0);
}

int	set_signals_as_here_doc(void)
{
	struct sigaction	as_here_doc;

	as_here_doc.sa_handler = signal_handler_as_here_doc;
	sigemptyset(&as_here_doc.sa_mask);
	as_here_doc.sa_flags = 0;
	if (sigaction(SIGINT, &as_here_doc, NULL) == -1
		|| sigaction(SIGQUIT, &as_here_doc, NULL) == -1)
		return (-1);
	else
		return (0);
}

int	set_signals_as_parent(void)
{
	struct sigaction	as_parent;

	as_parent.sa_handler = signal_handler_as_parent;
	sigemptyset(&as_parent.sa_mask);
	as_parent.sa_flags = 0;
	if (sigaction(SIGINT, &as_parent, NULL) == -1
		|| sigaction(SIGQUIT, &as_parent, NULL) == -1
		|| sigaction(SIGTERM, &as_parent, NULL) == -1)
		return (-1);
	else
		return (0);
}
