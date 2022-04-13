/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:47:19 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"

# include "ast.h"
# include "env.h"
# include "signals.h"
# include "builtins.h"
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

# define COMMAND_NOT_FOUND "Minishell: %s: command not found\n"
# define ERROR_ERRNO "Minishell: %s: %s\n"
# define PIPE_ERROR "Minishell: Pipe error occured\n"
# define FORK_ERROR "Minishell: Fork error occured\n"
# define EXECUTION_ERROR "Minishell: Error occured during execution\n"
# define HERE_DOC_EOF "Minishell: warning: here-document at line %i \
delimited by end-of-file (wanted `%s')\n"

typedef struct s_command
{
	char				*name;
	char				*original_name;
	char				**args;
	int					in_errno;
	char				*in_name;
	int					io_in_redirect;
	int					out_errno;
	char				*out_name;
	int					io_out_redirect;
	bool				is_piped;
	bool				error;
	pid_t				pid;
	struct s_command	*next;
}	t_command;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

void		add_command_to_args(t_command *command);
char		*ft_strtrunc(char **str, const char delim);
t_command	*parse_commands(t_ast_tree_node *root, t_dlist *vars);
void		replace_by_path(t_command *command, t_dlist *vars);
int			execute_file(t_command *command, t_minishell minishell,
				int forking, int save_stdin);
int			is_builtin(char *str);
int			exec_builtin(t_command *command, t_minishell minishell,
				int save_stdin, int forking);
void		free_cmd(t_command *cmd);

#endif