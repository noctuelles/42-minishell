/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/15 14:54:46 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "ast.h"
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_command
{
	char *name;
	char *original_name;
	char **args;
	int in_errno;
	char *in_name;
	int	io_in_redirect;
	int out_errno;
	char *out_name;
	int io_out_redirect;
	bool is_piped;
	struct s_command *next;
	bool error;
}	t_command;

typedef struct s_args
{
	char *value;
	struct s_args *next;
}	t_args;

void	add_command_to_args(t_command *command);
char    *ft_strtrunc(char **str, const char delim);
t_command *parse_commands(t_ast_tree_node *root);
void replace_by_path(t_command *command);
int	execute_file(t_command *command, char **envp);
int	is_builtin(char *str);

#endif