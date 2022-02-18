/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:52:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 19:43:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static t_command_list *get_fake_command_list()
{
	t_command_list *list1 = malloc(sizeof(t_command_list));
	t_command *command1 = malloc(sizeof(t_command));
	command1->name = strdup("cat");
	command1->args = malloc(sizeof(char*) * 2);
	command1->args[0] = strdup("-e");
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
	char *path = "/usr/sbin:/usr/bin";
	return NULL;
}

int	execute(t_command *command, t_command_separator separator_to_next)
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
			{
				printf("Execute: %s\n", path);
			}
		}
	}
	else
	{
		printf("Execute file from the gived path\n");
	}
}

int execute_list(t_command_list **list)
{
	t_command_list	*command_elem;

	command_elem = *list;
	while(command_elem != NULL)
	{
		execute(command_elem->command, command_elem->separator);
		command_elem = command_elem->next;
	}
}

int main()
{
	t_command_list *list = get_fake_command_list();
	execute_list(&list);
}