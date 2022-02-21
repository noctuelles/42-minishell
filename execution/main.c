/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:52:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/21 11:47:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "get_next_line.h"

static t_command_list *get_fake_command_list()
{
	t_command_list *list1 = malloc(sizeof(t_command_list));
	t_command *command1 = malloc(sizeof(t_command));
	command1->name = strdup("cat");
	command1->args = malloc(sizeof(char*) * 1);
	command1->args[0] = NULL;
	command1->redirection_count = 0;
	command1->redirections = NULL;
	list1->command = command1;
	list1->next = NULL;
	list1->separator = PIPE;

	t_command_list *list2 = malloc(sizeof(t_command_list));
	t_command *command2 = malloc(sizeof(t_command));
	command2->name = strdup("ls");
	command2->args = malloc(sizeof(char*) * 1);
	command2->args[0] = NULL;
	command2->redirection_count = 0;
	command2->redirections = NULL;
	list2->command = command2;
	list2->next = NULL;
	list2->separator = END;
	list1->next = list2;

	t_command_list *list3 = malloc(sizeof(t_command_list));
	t_command *command3 = malloc(sizeof(t_command));
	command3->name = strdup("ls");
	command3->args = malloc(sizeof(char*) * 1);
	command3->args[0] = NULL;
	command3->redirection_count = 0;
	command3->redirections = NULL;
	list3->command = command3;
	list3->next = NULL;
	list3->separator = END;
	//list2->next = list3;

	return list1;
}

char	*get_path_from_env(char *command_name)
{
	char *path = strdup("/usr/sbin:/usr/bin");
	int	 found;
	char *exec_path;

	found = 0;
	exec_path = NULL;
	if(!path)
		return NULL;
	while (ft_strtrunc(&path, ':'))
	{
		if(!found)
		{
			exec_path = malloc(sizeof(char) * (strlen(path) + strlen(command_name) + 2));
			exec_path[0] = '\0';
			strcat(exec_path, path);
			strcat(exec_path, "/");
			strcat(exec_path, command_name);
			if(access(exec_path, F_OK) == 0)
				found = 1;
			else
			{
				exec_path = NULL;
				free(exec_path);
			}
		}
	}
	return exec_path;
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

void	add_path_to_args(t_command *command, char *path)
{
	char	**args;
	int		length;
	int		i;

	args = command->args;
	length = 0;
	while(args[length])
		length++;
	command->args = malloc(sizeof(char *) * (length + 2));
	command->args[0] = path;
	i = -1;
	while(++i < length)
		command->args[i + 1] = args[i];
	free(args);
}

int	execute_file(t_command *command, char *path, char **envp, int is_piped)
{
	pid_t	pid;
	int		pipefd[2];
	int		wait_status;
	
	printf("Execute: %s\n", path);
	add_path_to_args(command, path);
	if(is_piped && pipe(pipefd) < 0)
		return -1;
	pid = fork();
	if(pid == -1)
		return -1;
	if(is_piped)
	{
		if(pid == 0)
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
		execve(path, command->args, envp);
		perror("Execution error");
		exit(errno);
	}
	else
	{
		return 1;
	}
}

int	execute(t_command *command, t_command_separator separator_to_next, char **envp)
{
	char	*path;
	
	printf("----------\nExecuting \'%s\' with args:\n", command->name);
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
				return(execute_file(command, path, envp, separator_to_next == PIPE));
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
			return(execute_file(command, path, envp, separator_to_next == PIPE));
	}
}

int execute_list(t_command_list **list, char **envp)
{
	t_command_list	*command_elem;
	int count;
	int i;
	int	status;
	char	*str;

	count = 0;
	command_elem = *list;
	while(command_elem != NULL)
	{
		count += (execute(command_elem->command, command_elem->separator, envp) == 1);
		command_elem = command_elem->next;
	}
	/*while(1)
	{
		str = get_next_line(0);
		if(!str)
			break;
		free(str);
	}*/
	i = -1;
	while(++i < count)
		waitpid(-1, &status, 0);
}

int main(int argc, char **argv, char **envp)
{
	t_command_list *list = get_fake_command_list();
	execute_list(&list, envp);
}