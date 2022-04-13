/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_appendix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:48:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/13 15:00:19 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_tree_node	*pipeline5(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;

	cmd_node = simple_cmd(parser);
	if (match(parser, T_NULL, NULL) == false)
		return (quit_production(parser, cmd_node, NULL, ERR_EXPECTED_COMMAND));
	return (cmd_node);
}
