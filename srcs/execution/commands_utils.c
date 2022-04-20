/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:05:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/20 13:37:05 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->here_doc = -1;
	return (command);
}

void	free_cmd(t_command *cmd)
{
	if (cmd->name && cmd->is_name_malloc)
		free(cmd->name);
	free(cmd->args);
	if (cmd->io_in_fd > 0)
		close(cmd->io_in_fd);
	if (cmd->io_out_fd > 0)
		close(cmd->io_out_fd);
	if (cmd->here_doc > 0)
		close(cmd->here_doc);
	ft_dlstclear(&cmd->io_in, NULL);
	ft_dlstclear(&cmd->io_out, NULL);
	free(cmd);
}

void	free_cmd_pipeline(t_command *first)
{
	t_command	*tmp;

	while (first != NULL)
	{
		tmp = first->next;
		free_cmd(first);
		first = tmp;
	}
}

void	add_command(t_command *cmd, t_command **lst)
{
	t_command	*elem;

	if (*lst == NULL)
		*lst = cmd;
	else
	{
		elem = *lst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = cmd;
	}
}

t_command	*test_parse_and_add(t_ast_tree_node *root, t_minishell *minishell,
	t_command **first, bool forking)
{
	t_command	*cur;

	cur = parse_command(root, forking, minishell);
	if (!cur)
	{
		display_error_more(NULL, "malloc", 0);
		free_cmd_pipeline(*first);
		return (NULL);
	}
	add_command(cur, first);
	return (cur);
}
