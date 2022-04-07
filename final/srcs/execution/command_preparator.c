/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_preparator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:52:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/07 12:49:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

char	*create_path(char *path, char *command_name)
{
	char	*exec_path;

	exec_path = malloc(sizeof(char)
			* (strlen(path) + strlen(command_name) + 2));
	exec_path[0] = '\0';
	strcat(exec_path, path);
	strcat(exec_path, "/");
	strcat(exec_path, command_name);
	return (exec_path);
}

void	not_found(char **exec_path)
{
	free(*exec_path);
	*exec_path = NULL;
}

char	*get_path_from_env(char *command_name, t_dlist *vars)
{
	char	*path;
	char	*cpy;
	int		found;
	char	*exec_path;

	found = 0;
	exec_path = NULL;
	if (get_var(vars, "PATH") != NULL)
	{
		cpy = strdup(get_var(vars, "PATH")->value);
		path = cpy;
		while (ft_strtrunc(&path, ':'))
		{
			if (!found)
			{
				exec_path = create_path(path, command_name);
				if (access(exec_path, F_OK) == 0)
					found = 1;
				else
					not_found(&exec_path);
			}
		}
		free(cpy);
	}
	return (exec_path);
}

void	replace_by_path(t_command *command, t_dlist *vars)
{
	char	*path;

	while (command != NULL)
	{
		command->original_name = command->name;
		if (strchr(command->name, '/') == NULL)
		{
			if (!is_builtin(command->name))
			{
				path = get_path_from_env(command->name, vars);
				if (path == NULL)
					fprintf(stderr, "Minishell: %s: command not found\n",
						command->name);
				command->name = path;
			}
		}
		else
		{
			if (access(command->name, F_OK) != 0)
				fprintf(stderr, "Minishell: %s: %s\n", command->name,
					strerror(errno));
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
	command->args[i + 1] = NULL;
	free(args);
}
