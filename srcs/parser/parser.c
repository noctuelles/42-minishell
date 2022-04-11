/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/11 18:32:10 by plouvel          ###   ########.fr       */
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
	node_pipeline = NULL;
	while (cast_tkn(parser.tkns)->type != T_NULL)
	{
		/* Si au debut, on a pas une parenthese ouverte ou un token T_WORD,
		 * et bien c'est qu'on est sur une erreur de parsing directement.
		 * On cherche pas a savoir le pourquoi du comment ! */

		if (cast_tkn(parser.tkns)->type != T_OP_PRT
				&& cast_tkn(parser.tkns)->type != T_WORD)
		{
			ft_dprintf(0, "{1;33}An error occured while parsing, invalid start token : %s{0}\n", get_type(cast_tkn(parser.tkns)->type));
			return (NULL);
		}
		while (cast_tkn(parser.tkns)->type == T_OP_PRT)
		{
			// push_stack(parser.op_stack, new_token_type(T_OP_PRT));
			parser.tkns = parser.tkns->next;
		}
		if (cast_tkn(parser.tkns)->type != T_CL_PRT
				&& cast_tkn(parser.tkns)->type != T_NULL)
		{
			/* Ici on va obtenir le pipeline.
			 * On peut avoir des cas d'erreurs ici, il faut donc quitter pro-
			 * prement si il y en a. */

			node_pipeline = retrieve_pipeline(&parser);
			if (!node_pipeline)
			{
				ft_dprintf(0, "{1;33}An error occured while parsing : bad pipeline.{0}\n");
				return (NULL);
			}
		}
		if (parser.last_used_tkn->type == T_CL_PRT
				|| parser.last_used_tkn->type == T_LOG_AND
				|| parser.last_used_tkn->type == T_LOG_OR)
		{
			parser.tkns = parser.tkns->next;
		}
		ft_printf("Last token used :\n\t< {32}%s{0} > {1}Type{0} <{1;36}%s{0}>", parser.last_used_tkn->val, get_type(parser.last_used_tkn->type));
		parser.tkns = parser.last_used_tkn->lst_elem;
	}
	return (node_pipeline);
}

t_ast_tree_node	*parse(t_dlist **tkns)
{
	t_ast_tree_node	*ast_root;

	ast_root = parse_from_tkns(*tkns);
	ft_dlstclear(tkns, free_token);
	if (!ast_root)
	{
		return (NULL);
	}
	return (ast_root);
}
