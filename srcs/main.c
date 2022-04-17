/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/17 15:00:58 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
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
#include "get_next_line.h"
#include "signals.h"
#include "ft_dprintf.h"

void	free_cmd(t_command *cmd)
{
	int	i;

	if (cmd->name )
		free(cmd->name);
	i = -1;
	if (cmd->args)
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
	}
	free(cmd->args);
	if (cmd->io_in_fd > 0)
		close(cmd->io_in_fd);
	if (cmd->io_out_fd > 0)
		close(cmd->io_out_fd);
	free(cmd);
}

void	init_variable(int *forking, int *count, int *status, int *last_pid)
{
	*forking = 1;
	*count = 0;
	*status = 0;
	*last_pid = 0;
}

int	execute_pipeline(t_ast_tree_node *root, t_minishell *minishell)
{
	int			forking;
	int			count;
	int			status;
	int			last_pid;
	t_command	*first;

	init_variable(&forking, &count, &status, &last_pid);
	minishell->save_stdin = dup(0);
	first = parse_commands(root, minishell);
	if (g_sigint)
	{
		ast_tree_delete_node(root);
		return (cancel_everything(minishell, first));
	}
	forking = !(first->next == NULL && first->name && is_builtin(first->name));
	if (forking)
		set_signals_as_parent();
	while (first != NULL)
		count += treat_return_code(&first, execute_file(first, minishell, forking), &status, &last_pid);
	status = wait_for_result(count, last_pid, status);
	return (end_pipeline(minishell, status));
}

char	*build_prompt_prefix(const char *user, const char *pwd)
{
	char	*prompt;
	size_t	user_len;
	size_t	pwd_len;

	user_len = ft_strlen(user);
	pwd_len = ft_strlen(pwd);
	prompt = malloc((user_len + pwd_len + 5) * sizeof(char));
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strcat(prompt, user);
	prompt[user_len - 1] = '@';
	ft_strcat(prompt, pwd);
	ft_strcat(prompt, STR_PROMPT_ARROW);
	return (prompt);
}

char	*prompt_and_read(t_dlist *vars)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	char	*str;

	if (get_var(vars, "PWD") == NULL || get_var(vars, "USER") == NULL)
		return (readline(STR_STD_PROMPT));
	user = get_var(vars, "USER")->value;
	pwd = get_var(vars, "PWD")->value;
	prompt = build_prompt_prefix(user, pwd);
	if (!prompt)
		return (NULL);
	str = readline(prompt);
	free(prompt);
	return (str);
}

void	*display_error(void)
{
	ft_dprintf(STDERR_FILENO, STR_ERROR, strerror(errno));
	return (NULL);
}

void	*display_error_more(const char *fcnt_name)
{
	ft_dprintf(STDERR_FILENO, STR_ERROR_M, fcnt_name, strerror(errno));
	return (NULL);
}

char	*read_from_user(t_minishell *minishell)
{
	char	*str;
	char	*pnw;

	set_signals_as_prompt();
	if (refill_env(&(minishell->vars)) != 0)
		ft_exit(1, NULL, minishell);
	if (isatty(STDIN_FILENO) == 1)
		str = prompt_and_read(minishell->vars);
	else
	{
		str = get_next_line(STDIN_FILENO);
		if (str)
		{
			pnw = ft_strchr(str, '\n');
			if (pnw)
				*pnw = '\0';
		}
	}
	if (str == NULL)
		ft_exit(1, NULL, minishell);
	return (str);
}

void	start_exec(t_minishell *minishell, t_ast_tree_node	*root)
{
	if (root != NULL)
	{
		if (root->type == NODE_COMMAND || root->type == NODE_PIPE)
			minishell->last_ret = execute_pipeline(root, minishell);
		else
			parse_and_or(root, minishell);
	}
}

#include <assert.h>

int	main(int argc, char **argv, char **envp)
{
	t_dlist			*vars;
	char			*str;
	t_ast_tree_node	*root;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	vars = NULL;
	vars = import_var(&vars, envp);
	minishell.last_ret = 0;
	minishell.vars = vars;
	while (1)
	{
		str = read_from_user(&minishell);
		if (str)
		{
			if (str[0] == '\0')
				continue ;
			add_history(str);
			root = parse_from_str(str);
			if (root)
				start_exec(&minishell, root);
		}
	}
	return (0);
}
