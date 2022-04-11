/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/11 18:01:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static t_ast_tree_node	*retrieve_pipeline(t_parser *parser)
{
	t_ast_tree_node	*node_pipeline;

	node_pipeline = pipeline(parser);
	if (!node_pipeline)
	{
		if (parser->errcode == ERR_MALLOC)
			ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
		else
			ft_dprintf(STDERR_FILENO, STR_PARSE_ERROR,
					get_parser_error(parser->errcode), parser->last_used_tkn->val);
		return (NULL);
	}
	else
		return (node_pipeline);
}

t_token	*cast_tkn(t_dlist *elem)
{
	return ((t_token *) elem->content);
}

static t_ast_tree_node	*parse_from_tkns(t_dlist *tkns)
{
	t_parser		parser;
	t_ast_tree_node	*node_pipeline;

	parser.tkns = tkns;
	parser.errcode = NO_ERR;
	parser.output_stack = NULL;
	parser.op_stack = NULL;
	while (parser.tkns)
	{
		while (cast_tkn(parser.tkns)->type == T_OP_PRT)
		{
			push_stack(parser.op_stack, new_token_type(T_OP_PRT));
			parser.tkns = parser.tkns->next;
		}
		if (cast_tkn(parser.tkns)->type != T_CL_PRT
				&& cast_tkn(parser.tkns)->type != T_NULL)
		{
			// Ici on va obtenir le pipeline !
		}
		// Ici on va gerer la combinaison
	}
	//ft_printf("Last token used :\n\t< {32}%s{0} > {1}Type{0} <{1;36}%s{0}>", parser.last_used_tkn->val, get_type(parser.last_used_tkn->type));
	return (root);
}

t_ast_tree_node	*parse(t_dlist **tkns)
{
	t_ast_tree_node	*ast_root;

	ast_root = parse_from_tkns(*tkns);
	ft_dlstclear(tkns, free_token);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}
