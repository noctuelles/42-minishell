/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:47:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 21:28:42 by dhubleur         ###   ########.fr       */
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

# define STR_CMD_NOT_FOUND  "minishell: %s: command not found.\n"
# define PIPE_ERROR         "minishell: pipe error occured\n"
# define FORK_ERROR         "minishell: fork error occured\n"
# define STR_EXEC_ERROR     "minishell: error occured during execution: "
# define HERE_DOC_EOF       "minishell: warning: here-document at line %i \
delimited by end-of-file (wanted `%s')\n"
# define END_BY_SIGNAL      "minishell: process %i terminated by a signal \
(%i)\n"
# define QUIT               "Quit (core dumped)\n"

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
int			exec_builtin(t_command *command, t_minishell *minishell,
				int forking);
void		free_cmd(t_command *cmd);
int			cancel_everything(t_minishell *minishell, t_command *cmd);
int			treat_return_code(t_command **cmd, int ret, int *status,
				int *last_pid);
int			wait_for_result(int count, int last_pid, int status);
int			end_pipeline(t_minishell *minishell, int status);
void		parse_and_or(t_ast_tree_node *node, t_minishell *minishell);
int			execute_pipeline(t_ast_tree_node *root, t_minishell *minishell);
int			execute_file(t_command *command, t_minishell *minishell,
				int forking);
int			prepare_fd(t_command *command);
void		free_cmd_pipeline(t_command *first);
int			pipeline_clean(t_minishell *minishell, int code);
t_command	*test_parse_and_add(t_ast_tree_node *root, t_minishell *minishell,
				t_command **first, bool forking);
t_command	*parse_command(t_ast_tree_node *node, bool piped,
				t_minishell *minishell);
void		dup_for_pipe(t_command *command, int pid, int pipefd[2]);
void		close_all_error(t_command *command, int code);
void		dup_and_close(int fd1, int fd2);
void		dup_for_redirections(t_command *command, int pid);
void		error_exit(char *str, int errno_value);
char		*find_command_name(t_dlist *args);

/* path.c */

char		*get_path_from_name(char *name, t_minishell *minishell,
				t_command *command);

/* io.c */

void		*add_io(t_arg *node, t_command *command);
void		here_doc_logic(t_arg *node, t_command *command);

/* commands_utils.c */

t_command	*init_cmd(void);
bool		is_a_pipeline_node(t_ast_tree_node *node);

#endif
