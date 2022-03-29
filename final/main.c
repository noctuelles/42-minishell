/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/29 12:42:33 by dhubleur         ###   ########.fr       */
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

void	print_tokens(t_lexer lexer)
{
	for (size_t i = 0; i < lexer.idx; i++)
		printf("< '%s' %d >\n", lexer.tkns[i].val, lexer.tkns[i].type);
}

extern const char NODE_STR_EQU[][100] ;
void print(t_ast_tree_node *root, int spaces)
{
	for(int i = 0; i < spaces; i++)
		printf(" ");
	printf("%s : %s\n", NODE_STR_EQU[root->type], root->value);
	if (root->left != NULL)
	{
		for(int i = 0; i < spaces; i++)
			printf(" ");
		printf("Going to left:\n");
		print(root->left, spaces + 1);
	}
	if (root->right != NULL)
	{
		for(int i = 0; i < spaces; i++)
			printf(" ");
		printf("Going to right:\n");
		print(root->right, spaces + 1);
	}
}

void treat_result(int pid, int wait_status, int *pipeline_result, int last_pid)
{
	if(WIFEXITED(wait_status))
	{
		if(last_pid != 0 && pid == last_pid)
		{
			*pipeline_result = WEXITSTATUS(wait_status);
		}
	}
	else if(WIFSIGNALED(wait_status))
	{
		if(__WCOREDUMP(wait_status))
			fprintf(stderr, "minishell: process %i terminated by a signal (%i)\n", pid, WTERMSIG(wait_status));
		if(last_pid != 0 && pid == last_pid)
			*pipeline_result = 128 + WTERMSIG(wait_status);
	}
}

void free_cmd(t_command *cmd)
{
	free(cmd->args);
	free(cmd);
}

int	execute_pipeline(t_ast_tree_node *root, t_dlist *env)
{
	int save_stdin = dup(0);
	t_command *first = parse_commands(root, env);
	t_command *save;
	int forking = 1;
	if(first->next == NULL && is_builtin(first->name))
		forking = 0;
	replace_by_path(first, env);
	int count = 0;
	int status = 0;
	int last_pid = 0;
	while(first != NULL)
	{
		int ret = execute_file(first, env, forking, save_stdin);
		if(ret == 4242)
			count++;
		if(first->next == NULL)
		{
			if(ret != 4242)
				status = ret;
			else
				last_pid = first->pid;
		}
		save = first;
		first = first->next;
		free_cmd(save);
	}
	if(forking)
	{
		int i = -1;
		int wait_status;
		while (++i < count)
		{
			int pid = waitpid(-1, &wait_status, 0);
			close(0);
			treat_result(pid, wait_status, &status, last_pid);
		}
	}
	close(0);
	dup2(save_stdin, 0);
	close(save_stdin);
	return status;
}

char *prompt_and_read(t_dlist *vars)
{
	if(get_var(vars, "PWD") == NULL || get_var(vars, "USER") == NULL)
		return (readline("Minishell > "));
	char *USER = get_var(vars, "USER")->value;
	char *PWD = get_var(vars, "PWD")->value;
	char *prompt = malloc(sizeof(char) * (ft_strlen(USER) + ft_strlen(PWD) + 6));
	if(!prompt)
		return NULL;
	prompt[0] = '\0';
	strcat(prompt, USER);
	strcat(prompt, "@");
	strcat(prompt, PWD);
	strcat(prompt, " > ");
	char *str = readline(prompt);
	free(prompt);
	return str;
}

void refill_env(t_dlist **env)
{
	if(get_var(*env, "PWD") == NULL)
	{
		char *pwd = calloc(sizeof(char), 1000);
		pwd = getcwd(pwd, 1000);
		if(!pwd)
		{
			perror("get working directory error");
			return ;
		}
		t_var	var;
		var.name = "PWD";
		var.value = pwd;
		var.inherit = FALSE;
		add_var(env, var);
	}
}

int	ft_exit(int argc, char **argv, t_dlist *env, int save_stdin);

void	signal_handler_as_prompt(int signum)
{
	if(signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_dlist *vars = NULL;
	
	vars = import_var(&vars, envp);
	while (1)
	{
		t_lexer	lexer = {0};
		t_ast_tree_node	*root;
		signal(SIGINT, signal_handler_as_prompt);
		signal(SIGQUIT, signal_handler_as_prompt);
		char *str = prompt_and_read(vars);
		if (str == NULL)
			ft_exit(1, NULL, vars, 0);
		add_history(str);
		fill_lexer_from_str(&lexer, str);
		root = parse(&lexer);
		refill_env(&vars);
		if (root != NULL)
		{
			execute_pipeline(root, vars);
			free_lexer(&lexer);
		}
	}
	return (0);
}