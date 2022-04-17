/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/17 14:35:22 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

# include "libft.h"

# include "ast.h"
# include "env.h"
# include "signals.h"
# include "builtins.h"
# include "parser.h"

# define COMMAND_NOT_FOUND "Minishell: %s: command not found\n"
# define ERROR_ERRNO "Minishell: %s: %s\n"
# define PIPE_ERROR "Minishell: Pipe error occured\n"
# define FORK_ERROR "Minishell: Fork error occured\n"
# define EXECUTION_ERROR "Minishell: Error occured during execution\n"
# define HERE_DOC_EOF "Minishell: warning: here-document at line %i \
delimited by end-of-file (wanted `%s')\n"
# define END_BY_SIGNAL "Minishell: process %i terminated by a signal (%i)\n"
# define QUIT "Quit (core dumped)\n"

extern int	g_sigint;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					here_doc;
	t_dlist				*io_in;
	t_dlist				*io_out;
	int					io_in_fd;
	int					io_out_fd;
	bool				is_piped;
	pid_t				pid;
	int					empty_command;
	struct s_command	*next;
}	t_command;

void		add_command_to_args(t_command *command);
char		*ft_strtrunc(char **str, const char delim);
t_command	*parse_commands(t_ast_tree_node *root, t_minishell *minishell);
void		replace_by_path(t_command *command, t_minishell *minishell);
int			is_builtin(char *str);
int			exec_builtin(t_command *command, t_minishell *minishell, int forking);
void		free_cmd(t_command *cmd);
int			cancel_everything(t_minishell *minishell, t_command *cmd);
int			treat_return_code(t_command **cmd, int ret, int *status,
				int *last_pid);
int			wait_for_result(int count, int last_pid, int status);
int			end_pipeline(t_minishell *minishell, int status);
void		parse_and_or(t_ast_tree_node *node, t_minishell *minishell);
int			execute_pipeline(t_ast_tree_node *root, t_minishell *minishell);
int			execute_file(t_command *command, t_minishell *minishell, int forking);
int			prepare_fd(t_command *command);

#endif