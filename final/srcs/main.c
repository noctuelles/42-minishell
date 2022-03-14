/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:36:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/14 12:24:55 by dhubleur         ###   ########.fr       */
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

t_command *parse_commands(t_ast_tree_node *root);
void replace_by_path(t_command *command);
int	execute_file(t_command *command, char **envp);

int main(int argc, char **argv, char **envp)
{
	t_lexer	lexer = {0};
	t_ast_tree_node	*root;

	
	char *str  = readline("> ");
		
	add_history(str);
	fill_lexer_from_str(&lexer, str);
	//print_tokens(lexer);
	root = parse(&lexer);
	//ast_tree_print_graph(root);
	printf("\e[0m\n");

	//print(root, 0);
	t_command *first = parse_commands(root);
	replace_by_path(first);

	int count = 0;
	while(first != NULL)
	{
		if(first->name != NULL)
		{
			execute_file(first, envp);
			count++;
		}
		first = first->next;
	}
	int i = -1;
	int status;
	while (++i < count)
	{
		waitpid(-1, &status, 0);
		close(0);
	}
	free_lexer(&lexer);
	return (0);
}
