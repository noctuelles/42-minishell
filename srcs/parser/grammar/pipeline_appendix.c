/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_appendix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:48:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/12 18:49:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_tree_node	*pipeline5(t_parser *parser)
{
	t_ast_tree_node	*cmd_node;

	cmd_node = simple_cmd(parser);
	if (match(parser, T_NULL, NULL) == false)
		return (quit_production(parser, NULL, cmd_node, ERR_EXPECTED_COMMAND));
	return (cmd_node);
}
