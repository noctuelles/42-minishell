/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:39:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/20 14:31:16 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ft_dprintf.h"
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

int	init_variable(int *count, int *status, int *last_pid,
			t_minishell *minishell)
{
	*count = 0;
	*status = 0;
	*last_pid = 0;
	minishell->save_stdin = dup(STDIN_FILENO);
	return (1);
}

int	execute_pipeline(t_ast_tree_node *root, t_minishell *minishell)
{
	int			forking;
	int			count;
	int			status;
	int			last_pid;
	t_command	*first;

	forking = init_variable(&count, &status, &last_pid, minishell);
	first = parse_commands(root, minishell);
	if (!first)
		return (1);
	minishell->current_pipeline_first = first;
	if (g_sigint)
		return (pipeline_clean(minishell, 130));
	forking = !(first->next == NULL && first->name && is_builtin(first->name));
	if (forking)
		set_signals_as_parent();
	while (first != NULL && !g_sigint)
		count += treat_return_code(&first,
				execute_file(first, minishell, forking), &status, &last_pid);
	if (g_sigint)
		return (pipeline_clean(minishell, 1));
	status = wait_for_result(count, last_pid, status);
	if (g_sigint)
		return (pipeline_clean(minishell, 130));
	return (pipeline_clean(minishell, status));
}

void	start_exec(t_minishell *minishell)
{
	if (is_a_pipeline_node(minishell->root))
		minishell->last_ret = execute_pipeline(minishell->root, minishell);
	else
		parse_and_or(minishell->root, minishell);
	ast_tree_delete_node(minishell->root);
	minishell->root = NULL;
}

void	*setup_minishell(int argc, char **argv, t_minishell *minishell,
		char **envp)
{
	(void) argc;
	(void) argv;
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->vars = import_var(minishell, envp);
	if (!minishell->vars && minishell->err)
		return (display_error_more(NULL, STR_MALLOC, 0));
	else if (!minishell->vars)
		ft_dprintf(STDERR_FILENO, STR_ENV_WARNING);
	return (minishell);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;

	if (!setup_minishell(argc, argv, &minishell, envp))
		return (1);
	minishell.root = NULL;
	minishell.current_pipeline_first = NULL;
	while (1)
	{
		minishell.err = 0;
		minishell.cmd_str = read_from_user(&minishell);
		if (minishell.cmd_str)
		{
			if (minishell.cmd_str[0] == '\0')
				continue ;
			add_history(minishell.cmd_str);
			minishell.root = parse_from_str(minishell.cmd_str);
			free(minishell.cmd_str);
			if (minishell.root)
				start_exec(&minishell);
		}
	}
	return (0);
}
