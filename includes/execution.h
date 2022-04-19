/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/19 18:08:49 by plouvel          ###   ########.fr       */
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


# define STR_CMD_NOT_FOUND  STR_SHELL_NAME ": %s: command not found.\n"
# define ERROR_ERRNO "Minishell: %s: %s\n"
# define PIPE_ERROR "Minishell: Pipe error occured\n"
# define FORK_ERROR "Minishell: Fork error occured\n"
# define STR_EXEC_ERROR     STR_SHELL_NAME ": error occured during execution: "
# define HERE_DOC_EOF "Minishell: warning: here-document at line %i \
delimited by end-of-file (wanted `%s')\n"
# define END_BY_SIGNAL "Minishell: process %i terminated by a signal (%i)\n"
# define QUIT "Quit (core dumped)\n"

extern int	g_sigint;

typedef struct s_command
{
	char				*name;
	int					is_name_malloc;
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
void	free_command_pipeline(t_command *first);
int	pipeline_clean(t_minishell *minishell, int code);

/* path.c */

char	*get_path_from_name(char *name, t_minishell *minishell,
	t_command *command);

/* io.c */

void	*add_io(t_arg *node, t_command *command);
void	here_doc_logic(t_arg *node, t_command *command);

/* commands_utils.c */

t_command	*init_cmd(void);





#endif
