/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/12 17:42:06 by dhubleur         ###   ########.fr       */
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

extern int	g_sigint;

void	treat_result(int pid, int wait_status, int *pipeline_result,
	int last_pid)
{
	if (WIFEXITED(wait_status))
	{
		if (last_pid != 0 && pid == last_pid)
			*pipeline_result = WEXITSTATUS(wait_status);
	}
	else if (WIFSIGNALED(wait_status))
	{
		if (WTERMSIG(wait_status) == 3)
		{
			if (!g_sigint)
			{
				fprintf(stderr, "Quit (core dumped)\n");
				g_sigint = 1;
			}
		}
		else if (__WCOREDUMP(wait_status))
			fprintf(stderr, "minishell: process %i terminated by a signal (%i)\n", pid, WTERMSIG(wait_status));
		if (last_pid != 0 && pid == last_pid)
			*pipeline_result = 128 + WTERMSIG(wait_status);
	}
}

void	free_cmd(t_command *cmd)
{
	int	i;
	if(cmd->name != cmd->original_name)
	{
		free(cmd->name);
		free(cmd->original_name);
	}
	else
		free(cmd->name);
	i = 0;
	if(cmd->args && cmd->args[0])
	{
		while(cmd->args[++i])
			free(cmd->args[i]);
	}
	free(cmd->args);
	free(cmd);
}

int	treat_return_code(t_command **cmd, int ret, int *status, int *last_pid)
{
	int			count;
	t_command	*first;

	first = *cmd;
	count = 0;
	if (ret == 4242)
		count = 1;
	if (first->next == NULL)
	{
		if (ret != 4242)
			*status = ret;
		else
			*last_pid = first->pid;
	}
	*cmd = first->next;
	free_cmd(first);
	return (count);
}

int	end_pipeline(int save_stdin, int status)
{
	set_signals_as_prompt();
	g_sigint = 0;
	close(0);
	dup2(save_stdin, 0);
	close(save_stdin);
	return (status);
}

int	cancel_everything(int save_stdin, t_command *cmd)
{
	t_command *tmp;

	g_sigint = 0;
	dup2(save_stdin, 0);
	close(save_stdin);
	while(cmd)
	{
		tmp = cmd->next;
		free_cmd(cmd);
		cmd = tmp;
	}
	return (130);
}

int wait_for_result(int count, int last_pid)
{
	int	i;
	int	pid;
	int	wait_status;
	int	status;

	i = -1;
	status = 0;
	while (++i < count)
	{
		pid = waitpid(-1, &wait_status, 0);
		close(0);
		treat_result(pid, wait_status, &status, last_pid);
	}
	return (status);
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
	int			save_stdin;
	int			forking;
	int			count;
	int			status;
	int			last_pid;
	t_command	*first;
	t_dlist		*env;

	env = minishell.vars;
	init_variable(&forking, &count, &status, &last_pid);
	save_stdin = dup(0);
	first = parse_commands(root, env);
	if (g_sigint)
	{
		ast_tree_delete_node(root);
		return (cancel_everything(save_stdin, first));
	}
	forking = !(first->next == NULL && is_builtin(first->name));
	replace_by_path(first, env);
	ast_tree_delete_node(root);
	if (forking)
		set_signals_as_parent();
	while (first != NULL)
		count += treat_return_code(&first, execute_file(first, minishell, forking,
					save_stdin), &status, &last_pid);
	status = wait_for_result(count, last_pid);
	return (end_pipeline(save_stdin, status));
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

void refill_env(t_dlist **env)
{
	char	*pwd;
	t_var	var;

	if (get_var(*env, "PWD") == NULL)
	{
		pwd = calloc(sizeof(char), 1000);
		pwd = getcwd(pwd, 1000);
		if (!pwd)
		{
			perror("get working directory error");
			return ;
		}
		var.name = "PWD";
		var.value = pwd;
		var.inherit = FALSE;
		add_var(env, var);
	}
}

int	ft_exit(int argc, char **argv, t_minishell minishell, int save_stdin);

int main(int argc, char **argv, char **envp)
{
	t_dlist			*vars;
	t_ast_tree_node	*root;
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
		set_signals_as_prompt();
		refill_env(&vars);
		if(isatty(0) == 1)
		{
			str = prompt_and_read(vars);
			add_history(str);
		}
		else
		{
			str = get_next_line(0);
			if(str && strchr(str, '\n') != NULL)
				*strchr(str, '\n') = 0;
		}
		if (str == NULL)
			ft_exit(1, NULL, minishell, 0);
		refill_env(&vars);
		if(strcmp(str, "") == 0)
			continue;
		tkns = get_tokens(str, vars);
		if (tkns)
		{
			root = parse(&tkns);
			if (root != NULL)
				minishell.last_ret = execute_pipeline(root, minishell);
		}
		else
			fprintf(stderr, "Les tokens ca marche pas\n");
	}
	return (0);
}
