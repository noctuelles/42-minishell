/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:32:11 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:34:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

int		set_signals_as_prompt(void);
int		set_signals_as_here_doc(void);
int		set_signals_as_parent(void);

void	signal_handler_as_prompt(int signum);
void	signal_handler_as_here_doc(int signum);
void	signal_handler_as_parent(int signum);

#endif
