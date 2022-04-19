/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:10:21 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/19 16:20:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void	signal_handler_as_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_as_here_doc(int signum)
{
	if (signum == SIGINT)
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
