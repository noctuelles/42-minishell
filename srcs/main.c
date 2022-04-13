/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 17:59:04 by dhubleur         ###   ########.fr       */
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

void	free_cmd(t_command *cmd)
{
	int	i;

	if (cmd->name != cmd->original_name)
	{
		free(cmd->name);
		free(cmd->original_name);
	}
	else
		free(cmd->name);
	i = 0;
	if (cmd->args && cmd->args[0])
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
	}
	free(cmd->args);
	if (cmd->io_in_redirect > 0)
		close(cmd->io_in_redirect);
	if (cmd->io_out_redirect > 0)
		close(cmd->io_out_redirect);
	free(cmd);
}

void	init_variable(int *forking, int *count, int *status, int *last_pid)
{
	*forking = 1;
	*count = 0;
	*status = 0;
	*last_pid = 0;
}

int	execute_pipeline(t_ast_tree_node *root, t_minishell minishell)
{
	int			forking;
	int			count;
	int			status;
	int			last_pid;
	t_command	*first;

	init_variable(&forking, &count, &status, &last_pid);
	minishell.save_stdin = dup(0);
	first = parse_commands(root, minishell.vars);
	if (g_sigint)
	{
		ast_tree_delete_node(root);
		return (cancel_everything(minishell.save_stdin, first));
	}
	forking = !(first->next == NULL && is_builtin(first->name));
	replace_by_path(first, minishell.vars);
	ast_tree_delete_node(root);
	if (forking)
		set_signals_as_parent();
	while (first != NULL)
		count += treat_return_code(&first, execute_file(first, minishell,
					forking, minishell.save_stdin), &status, &last_pid);
	status = wait_for_result(count, last_pid, status);
	return (end_pipeline(minishell.save_stdin, status));
}

char	*prompt_and_read(t_dlist *vars)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	char	*str;

	if (get_var(vars, "PWD") == NULL || get_var(vars, "USER") == NULL)
		return (readline("Minishell > "));
	user = get_var(vars, "USER")->value;
	pwd = get_var(vars, "PWD")->value;
	prompt = malloc(sizeof(char) * (
				ft_strlen(user) + ft_strlen(pwd) + 6));
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	strcat(prompt, user);
	strcat(prompt, "@");
	strcat(prompt, pwd);
	strcat(prompt, " > ");
	str = readline(prompt);
	free(prompt);
	return (str);
}

char	*before_read(t_dlist **vars, t_minishell minishell)
{
	char	*str;

	set_signals_as_prompt();
	refill_env(vars);
	if (isatty(0) == 1)
		str = prompt_and_read(*vars);
	else
	{
		str = get_next_line(0);
		if (str && strchr(str, '\n') != NULL)
			*strchr(str, '\n') = 0;
	}
	if (str == NULL)
		ft_exit(1, NULL, minishell, 0);
	refill_env(vars);
	return (str);
}

void	start_exec(t_minishell *minishell, t_dlist *tkns)
{
	t_ast_tree_node	*root;

	root = parse(&tkns);
	if (root != NULL)
	{
		if (root->type == NODE_COMMAND || root->type == NODE_PIPE)
			minishell->last_ret = execute_pipeline(root, *minishell);
		else
			parse_and_or(root, minishell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist			*vars;
	char			*str;
	t_dlist			*tkns;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	vars = NULL;
	vars = import_var(&vars, envp);
	minishell.last_ret = 0;
	minishell.vars = vars;
	while (1)
	{
		str = before_read(&vars, minishell);
		if (strcmp(str, "") == 0)
			continue ;
		add_history(str);
		tkns = get_tokens(str, vars);
		free(str);
		if (tkns)
			start_exec(&minishell, tkns);
	}
	return (0);
}
