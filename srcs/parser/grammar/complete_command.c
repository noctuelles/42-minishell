/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:28:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 10:29:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*COMPLETE_CMD(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	rslt = AND_OR(parser);
	if (rslt)
	{
		if (match(parser, T_NULL, NULL) == FALSE)
		{
			ast_tree_delete_node(rslt);
			return (NULL);
		}
	}
	return (rslt);
}
