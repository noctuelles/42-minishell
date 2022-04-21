/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:19:31 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 21:27:19 by dhubleur         ###   ########.fr       */
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
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, signal_handler_as_prompt);
	return (1);
}

int	set_signals_as_here_doc(void)
{
	signal(SIGINT, signal_handler_as_here_doc);
	signal(SIGQUIT, signal_handler_as_here_doc);
	return (1);
}

int	set_signals_as_parent(void)
{
	signal(SIGINT, signal_handler_as_parent);
	signal(SIGQUIT, signal_handler_as_parent);
	signal(SIGTERM, signal_handler_as_parent);
	return (1);
}
