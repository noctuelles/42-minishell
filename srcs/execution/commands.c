/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:58:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/19 18:09:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* gestions d'erreurs et simplification */

void	*parse_list(t_dlist *node, t_command *command, int *arg_count)
{
	t_arg_type	arg_type;

	arg_type = ((t_arg *) node->content)->type;
	if (arg_type == ARG_WORD)
		(*arg_count)++;
	else if (arg_type == ARG_REDIRECT_HERE_DOC)
		here_doc_logic(node->content, command);
	else
	{
		if (!add_io(node->content, command))
			return (NULL);
	}
	if (node->next && !g_sigint)
	{
		if (!parse_list(node->next, command, arg_count))
			return (NULL);
	}
	return (node);
}

t_command	*prepare_command(bool piped, t_ast_tree_node *node,
	int *arg_count, t_minishell *minishell)
{
	t_command	*command;

	command = init_cmd();
	if (node->args != NULL)
	{
		command->is_piped = piped;
		command->name = get_path_from_name(
				((t_arg *)node->args->content)->value, minishell, command);
		if (!command->name)
			return (command);
		*arg_count = 1;
		if (node->args->next != NULL)
			parse_list(node->args->next, command, arg_count);
	}
	else
	{
		command->empty_command = 1;
		command->name = NULL;
	}
	return (command);
}

t_command	*parse_command(t_ast_tree_node *node, bool piped,
	t_minishell *minishell)
{
	t_command	*command;
	int			args_count;
	t_dlist		*elem;
	int			i;

	command = prepare_command(piped, node, &args_count, minishell);
	if (command->name != NULL && !g_sigint)
	{
		command->args = ft_calloc(sizeof(char *), args_count + 1);
		elem = node->args;
		i = 0;
		while (elem)
		{
			if (((t_arg *)elem->content)->type == ARG_WORD)
			{
				command->args[i] = ((t_arg *)elem->content)->value;
				i++;
			}
			elem = elem->next;
		}
	}
	command->next = NULL;
	return (command);
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

t_command	*parse_commands(t_ast_tree_node *root, t_minishell *minishell)
{
	t_command	*first;

	(void)minishell->vars;
	first = NULL;
	apply_expansion_on_node(root, minishell);
	if (root->type == NODE_COMMAND)
	{
		first = parse_command(root, false, minishell);
	}
	else
	{
		while (root->type == NODE_PIPE && !g_sigint)
		{
			add_command(parse_command(root->left, true, minishell), &first);
			root = root->right;
		}
		if (!g_sigint)
			add_command(parse_command(root, false, minishell), &first);
	}
	return (first);
}
