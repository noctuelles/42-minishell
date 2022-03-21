/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/21 21:31:51 by dhubleur         ###   ########.fr       */
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

void treat_result(int pid, int wait_status, int *pipeline_result)
{
	if(WIFEXITED(wait_status))
	{
		*pipeline_result = WEXITSTATUS(wait_status);
	}
	else if(WIFSIGNALED(wait_status))
	{
		if(__WCOREDUMP(wait_status))
			fprintf(stderr, "minishell: process %i terminated by a signal (%i)\n", pid, WTERMSIG(wait_status));
		*pipeline_result = 128 + WTERMSIG(wait_status);
	}
}

int	execute_pipeline(t_ast_tree_node *root, t_dlist *env, char **envp)
{
	int save_stdin = dup(0);
	t_command *first = parse_commands(root, env);
	int forking = 1;
	if(first->next == NULL && is_builtin(first->name))
		forking = 0;
	replace_by_path(first, env);
	int count = 0;
	while(first != NULL)
	{
		execute_file(first, envp, env, forking);
		count++;
		first = first->next;
	}
	int pipeline_result = 0;
	if(forking)
	{
		int i = -1;
		int status;
		while (++i < count)
		{
			int pid = waitpid(-1, &status, 0);
			close(0);
			treat_result(pid, status, &pipeline_result);
		}
	}
	dup2(save_stdin, 0);
	return pipeline_result;
}

char *prompt_and_read(t_dlist *vars)
{
	char *USER = get_var(vars, "USER")->value;
	if(!USER)
	{
		printf("USER variable not found\n");
		return NULL;
	}
	char *PWD = get_var(vars, "PWD")->value;
	if(!PWD)
	{
		printf("PWD variable not found\n");
		return NULL;
	}
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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_dlist *vars = NULL;
	
	vars = import_var(&vars, envp);
	
	while(1)
	{
		t_lexer	lexer = {0};
		t_ast_tree_node	*root;
		char *str = prompt_and_read(vars);
		if(str == NULL)
			exit(0);
			
		add_history(str);
		fill_lexer_from_str(&lexer, str);
		root = parse(&lexer);
		if(root != NULL)
		{
			execute_pipeline(root, vars, envp);
			free_lexer(&lexer);
		}
	}
	return (0);
}