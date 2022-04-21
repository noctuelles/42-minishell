/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:29:39 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/21 21:28:33 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "minishell.h"
#include "ft_dprintf.h"
#include "builtins.h"
#include "execution.h"
#include <stdlib.h>

char	*find_command_name(t_dlist *args)
{
	while (args)
	{
		if (((t_arg *)args->content)->type == ARG_WORD)
			return (((t_arg *)args->content)->value);
		args = args->next;
	}
	return (NULL);
}

static char	*create_path(char *path, char *command_name)
{
	char	*exec_path;

	exec_path = malloc(sizeof(char)
			* (ft_strlen(path) + ft_strlen(command_name) + 2));
	if (!exec_path)
		return (NULL);
	exec_path[0] = '\0';
	ft_strcat(exec_path, path);
	ft_strcat(exec_path, "/");
	ft_strcat(exec_path, command_name);
	return (exec_path);
}

static char	*search_accessible_path(t_minishell *minishell, char **paths,
		char *cmd_name)
{
	size_t	i;
	char	*abs_cmd_path;

	i = 0;
	while (paths[i] != NULL)
	{
		abs_cmd_path = create_path(paths[i], cmd_name);
		if (!abs_cmd_path)
			return (set_minishell_err_null(minishell, ERR_MALLOC));
		if (access(abs_cmd_path, F_OK | R_OK | X_OK) == 0)
			return (abs_cmd_path);
		else
			free(abs_cmd_path);
		i++;
	}
	return (NULL);
}

static char	*get_path_from_env(char *cmd_name, t_minishell *minishell)
{
	size_t	i;
	t_var	*path_var;
	char	**paths;
	char	*cmd_path;

	path_var = get_var(minishell->vars, "PATH");
	cmd_path = NULL;
	if (path_var)
	{
		paths = ft_split(path_var->value, ':');
		if (!paths)
			return (display_error_more(minishell, STR_MALLOC, ERR_MALLOC));
		cmd_path = search_accessible_path(minishell, paths, cmd_name);
		if (!cmd_path && minishell->err)
			display_error_more(NULL, STR_MALLOC, 0);
		i = 0;
		while (paths[i] != NULL)
			free(paths[i++]);
		free(paths);
	}
	return (cmd_path);
}

/* Si cette fonction retourne NULL et que minishell->var n'est pas à zéro,
 * il y a eu un gros problème */

char	*get_path_from_name(char *name, t_minishell *minishell,
	t_command *command)
{
	char	*path;

	if (!name)
		return (NULL);
	if (!ft_strchr(name, '/'))
	{
		if (!is_builtin(name))
		{
			command->is_name_malloc = 1;
			path = get_path_from_env(name, minishell);
			if (!path && !minishell->err)
				ft_dprintf(STDERR_FILENO, STR_CMD_NOT_FOUND, name);
			return (path);
		}
		else
			return (name);
	}
	else
	{
		if (access(name, F_OK | X_OK | R_OK) == 0)
			return (name);
		else
			return (display_error_more(NULL, name, 0));
	}
}
