/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:28:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/18 18:49:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*complete_cmd(t_parser *parser)
{
	t_ast_tree_node	*rslt;

	rslt = and_or(parser);
	if (rslt)
	{
		if (match(parser, T_NULL, NULL) == FALSE)
		{
			if (parser->errcode == NO_ERR)
				return (quit_production(parser, rslt, NULL,
						ERR_UNEXPECTED_EOF));
			else
				return (quit_production(parser, rslt, NULL, parser->errcode));
		}
	}
	return (rslt);
}
