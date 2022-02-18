/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:38:03 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 17:55:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

typedef enum e_command_separator
{
	PIPE,
	AND,
	OR
}	t_command_separator;

typedef enum e_redirection_type
{
	STDIN,
	HERE_DOC,
	STDOUT,
	STDOUT_APPEND
}	t_redirection_type;

typedef struct s_redirections
{
	t_redirection_type	type;
	char				*name;
}	t_redirections;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					redirection_count;
	t_redirections		*redirections;
}	t_command;

typedef struct s_command_list
{
	t_command 				*command;
	t_command_separator 	separator;
	struct s_command_list	*next;
}	t_command_list;

#endif