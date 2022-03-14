/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:47:44 by dhubleur          #+#    #+#             */
/*   Updated: 2022/03/14 17:25:22 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_args
{
	char *value;
	struct s_args *next;
}	t_args;

void	parse_tree(t_ast_tree_node *node, t_command *command, t_args **args)
{
	if(node->type == NODE_COMMAND_SUFFIX)
	{
		if(*args == NULL)
		{
			*args = calloc(sizeof(t_args), 1);
			(*args)->next = NULL;
			(*args)->value = node->value;
		}
		else
		{
			t_args *elem = *args;
			while(elem->next != NULL)
				elem = elem->next;
			elem->next = calloc(sizeof(t_args), 1);
			elem->next->next = NULL;
			elem->next->value = node->value;
		}
	}
	if(node->type == NODE_IO_REDIRECT_STDIN)
		command->io_in_redirect = node->value;
	if(node->type == NODE_IO_REDIRECT_FILE)
		command->io_out_redirect = node->value;
	if(node->left != NULL)
		parse_tree(node->left, command, args);
	if(node->right != NULL)
		parse_tree(node->right, command, args);
}

t_command	*parse_command(t_ast_tree_node *node, bool piped)
{
	t_command *command;
	t_args	*args;

	command = calloc(sizeof(t_command), 1);
	
	command->is_piped = piped;
	command->name = node->value;
	args = NULL;
	if(node->left != NULL)
		parse_tree(node->left, command, &args);
	if(node->right != NULL)
		parse_tree(node->right, command, &args);
	int length = 0;
	t_args *elem = args;
	while(elem)
	{
		length++;
		elem = elem->next;
	}
	command->args = calloc(sizeof(char*), length + 1);
	int i = 0;
	while(args)
	{
		command->args[i] = args->value;
		t_args *tmp = args;
		args = args->next;
		free(tmp);
		i++;
	}
	command->args[i] = NULL;
	command->next = NULL;
}

void	add_command(t_command *cmd, t_command **lst)
{
	t_command *elem;

	if(*lst == NULL)
		*lst = cmd;
	else
	{
		elem = *lst;
		while(elem->next != NULL)
			elem = elem->next;
		elem->next = cmd;
	}
}

t_command *parse_commands(t_ast_tree_node *root)
{
	t_command *first;

	first = NULL;
	if(root->type == NODE_COMMAND)
		first = parse_command(root, false);
	else
	{
		while(root->type == NODE_PIPE)
		{
			add_command(parse_command(root->left, true), &first);
			root = root->right;
		}
		add_command(parse_command(root, false), &first);
	}
	return (first);
}

int	is_builtin(char *str)
{
	if(strcmp(str, "echo") == 0)
		return 1;
	if(strcmp(str, "cd") == 0)
		return 1;
	if(strcmp(str, "pwd") == 0)
		return 1;
	if(strcmp(str, "export") == 0)
		return 1;
	if(strcmp(str, "unset") == 0)
		return 1;
	if(strcmp(str, "env") == 0)
		return 1;
	if(strcmp(str, "exit") == 0)
		return 1;
	return 0;
}

char    *ft_strtrunc(char **str, const char delim);

char	*get_path_from_env(char *command_name)
{
	char	*path = strdup("/usr/sbin:/usr/bin");
	int		found;
	char	*exec_path;

	found = 0;
	exec_path = NULL;
	if (!path)
		return (NULL);
	while (ft_strtrunc(&path, ':'))
	{
		if (!found)
		{
			exec_path = malloc(
					sizeof(char) * (strlen(path) + strlen(command_name) + 2));
			exec_path[0] = '\0';
			strcat(exec_path, path);
			strcat(exec_path, "/");
			strcat(exec_path, command_name);
			if (access(exec_path, F_OK) == 0)
				found = 1;
			else
			{
				free(exec_path);
				exec_path = NULL;
			}
		}
	}
	return (exec_path);
}

void replace_by_path(t_command *command)
{
	while(command != NULL)
	{
		command->original_name = command->name;
		if (strchr(command->name, '/') == NULL)
		{
			if (is_builtin(command->name))
			{
				printf("builtin\n");
			}
			else
			{
				char *path = get_path_from_env(command->name);
				if (path == NULL)
					printf("\n%s: command not found\n", command->name);
				command->name = path;
			}
		}
		else
		{
			if (access(command->name, F_OK) != 0)
				printf("\nMinishell: %s: No such file or directory\n", command->name);
		}
		command = command->next;
	}
}

void	add_command_to_args(t_command *command)
{
	char	**args;
	int		length;
	int		i;

	args = command->args;
	length = 0;
	while (args[length])
		length++;
	command->args = malloc(sizeof(char *) * (length + 2));
	command->args[0] = command->original_name;
	i = -1;
	while (++i < length)
		command->args[i + 1] = args[i];
	free(args);
}

int	execute_file(t_command *command, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	int		wait_status;

	add_command_to_args(command);
	if (command->is_piped && pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (command->is_piped)
	{
		if (pid == 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		else
		{
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}

	
	if(pid == 0)
	{
		if(command->io_in_redirect != NULL)
		{
			int fd = open(command->io_in_redirect, O_RDONLY);
			dup2(fd, 0);
		}
		if(command->io_out_redirect != NULL)
		{
			int fd = open(command->io_out_redirect, O_WRONLY | O_CREAT, 0777);
			dup2(fd, 1);
		}
		//dup stdin from a file
		/*int fd = open("test2", O_RDONLY);
		dup2(fd, 0);*/

		//dup stdout to a file by creating it if neeeded
		/*int fd2 = open("output", O_WRONLY | O_CREAT, 0777);
		dup2(fd2, 1);*/

		//dup stdout to a file by creating it if neeeded and append
		/*int fd3 = open("output2", O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(fd3, 1);*/
	}

	if (pid == 0 && command->name != NULL)
	{
		execve(command->name, command->args, envp);
		perror("Execution error");
		exit(errno);
	}
	else
		return (1);
}