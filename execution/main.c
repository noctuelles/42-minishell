/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:52:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/20 12:32:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static t_command_list *get_fake_command_list()
{
	t_command_list *list1 = malloc(sizeof(t_command_list));
	t_command *command1 = malloc(sizeof(t_command));
	command1->name = strdup("ls");
	command1->args = malloc(sizeof(char*) * 2);
	command1->args[0] = strdup("/usr/bin/ls");
	command1->args[1] = NULL;
	command1->redirection_count = 0;
	command1->redirections = NULL;
	list1->command = command1;
	list1->next = NULL;
	list1->separator = END;
	return list1;
}

char	*get_path_from_env(char *command_name)
{
	char *path = strdup("/usr/sbin:/usr/bin");
	char *exec_path;

	if(!path)
		return NULL;
	while (ft_strtrunc(&path, ':'))
	{
		exec_path = malloc(sizeof(char) * (strlen(path) + strlen(command_name) + 2));
		exec_path[0] = '\0';
		strcat(exec_path, path);
		strcat(exec_path, "/");
		strcat(exec_path, command_name);
		if(access(exec_path, F_OK) == 0)
			return exec_path;
		free(exec_path);
	}
	return NULL;
}

char	*get_path_from_pwd(char *command_name)
{
	char *pwd = strdup("/mnt/d/root/Files/Dev/C/42-minishell/execution");
	char *exec_path;

	exec_path = malloc(sizeof(char) * (strlen(pwd) + strlen(command_name) + 2));
	exec_path[0] = '\0';
	strcat(exec_path, pwd);
	strcat(exec_path, "/");
	strcat(exec_path, command_name);
	if(access(exec_path, F_OK) == 0)
		return exec_path;
	free(exec_path);
	return NULL;
}

int	execute_file(t_command *command, char *path, char **envp)
{
	int	pid;
	int	wait_status;
	
	printf("Execute: %s\n", path);
	pid = fork();
	if(pid == -1)
		return -1;
	if(pid == 0)
	{
		if(execve(path, command->args, envp) < 0)
			perror("Execution error");
	}
	else
	{
		waitpid(pid, &wait_status, 0);
		return wait_status;
	}
}

int	execute(t_command *command, t_command_separator separator_to_next, char **envp)
{
	char	*path;
	
	printf("Executing \'%s\' with args:\n", command->name);
	for(int i = 0; command->args[i]; i++)
		printf("- \'%s\'\n", command->args[i]);
	if(strchr(command->name, '/') == NULL)
	{
		if(is_builtin(command->name))
		{
			printf("Execute builtin\n");
		}
		else
		{
			printf("Execute from $PATH\n");
			path = get_path_from_env(command->name);
			if(path == NULL)
			{
				printf("%s: command not found\n", command->name);
				return -1;
			}
			else
				return(execute_file(command, path, envp));
		}
	}
	else
	{
		path = get_path_from_pwd(command->name);
		if(path == NULL)
		{
			printf("Minishell: %s: No such file or directory\n", command->name);
			return -1;
		}
		else
			return(execute_file(command, path, envp));
	}
}

int execute_list(t_command_list **list, char **envp)
{
	t_command_list	*command_elem;

	command_elem = *list;
	while(command_elem != NULL)
	{
		execute(command_elem->command, command_elem->separator, envp);
		command_elem = command_elem->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_command_list *list = get_fake_command_list();
	execute_list(&list, envp);
}