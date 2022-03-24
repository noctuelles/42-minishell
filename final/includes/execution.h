/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/24 15:06:31 by dhubleur         ###   ########.fr       */
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
	pid_t pid;
}	t_command;

typedef struct s_args
{
	char *value;
	struct s_args *next;
}	t_args;

void	add_command_to_args(t_command *command);
char    *ft_strtrunc(char **str, const char delim);
t_command *parse_commands(t_ast_tree_node *root, t_dlist *vars);
void replace_by_path(t_command *command, t_dlist *vars);
int	execute_file(t_command *command, t_dlist *vars, int forking, int save_stdin);
int	is_builtin(char *str);
int exec_builtin(char *str, char **argv, t_dlist *env, int save_stdin);

#endif