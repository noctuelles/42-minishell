/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_appendix.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:23:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/13 15:07:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include <stdlib.h>

t_ast_tree_node	*simple_cmd5(t_parser *parser)
{
	char			*cmd_name;
	t_ast_tree_node	*rslt;

	if (match(parser, T_WORD, &cmd_name) == FALSE)
		return (quit_production(parser, NULL, NULL, ERR_EXPECTED_COMMAND));
	rslt = ast_tree_create_node(cmd_name, NODE_COMMAND);
	if (!rslt)
	{
		free(cmd_name);
		return (quit_production(parser, NULL, NULL, ERR_MALLOC));
	}
	return (rslt);
}
