/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:19:31 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/04 11:45:19 by dhubleur         ###   ########.fr       */
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

void	signal_handler_as_prompt(int signum)
{
	if(signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_as_here_doc(int signum)
{
	if(signum == SIGINT)
	{
		g_sigint = 1;
		close(0);
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_as_parent(int signum)
{
	(void)signum;
}

void set_signals_as_prompt()
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, signal_handler_as_prompt);
}

void set_signals_as_here_doc()
{
	signal(SIGINT, signal_handler_as_here_doc);
	signal(SIGQUIT, signal_handler_as_here_doc);
}

void set_signals_as_parent()
{
	signal(SIGINT, signal_handler_as_parent);
	signal(SIGQUIT, signal_handler_as_parent);
}