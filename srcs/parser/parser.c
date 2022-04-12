/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/12 17:30:52 by plouvel          ###   ########.fr       */
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

static inline t_token	*cast_tkn(t_dlist *elem)
{
	return ((t_token *) elem->content);
}

static	t_ast_tree_node *create_node(t_parse_stack *out_stack, t_token_type type)
{
	t_ast_tree_node	*left;
	t_ast_tree_node	*right;
	t_ast_tree_node	*result;
	t_node_type		node_type;

	left = (t_ast_tree_node *) out_stack->top->prev->content;
	right = (t_ast_tree_node *) out_stack->top->content;
	if (type == T_LOG_AND)
		node_type = NODE_LOGICAL_AND;
	if (type == T_LOG_OR)
		node_type = NODE_LOGICAL_OR;
	result = ast_tree_create_node(NULL, node_type);
	if (!result)
		return (NULL);
	ast_tree_attach(result, left, right);
	pop_stack(out_stack, NULL, 2);
	push_stack(out_stack, result);
	return (result);
}

void	consume_token(t_parser *parser)
{
	parser->tkns = parser->tkns->next;
	parser->curr_tkn = (t_token *) parser->tkns->content;
}

static inline t_token_type	curr_type(t_parser parser)
{
	return (parser.curr_tkn->type);
}

static inline bool	is_top_an_operator(t_parser parser)
{
	t_token	*top_tkn;

	top_tkn = parser.op_stack.top->content;
	if (top_tkn->type == T_LOG_AND || top_tkn->type == T_LOG_OR)
		return (true);
	else
		return (false);
}

static void	update_tkns(t_parser *parser)
{
	parser->tkns = parser->last_used_tkn->lst_elem;
	parser->curr_tkn = (t_token *) parser->tkns->content;
}

static t_ast_tree_node	*parse_from_tkns(t_dlist *tkns)
{
	t_parser		parser;
	t_ast_tree_node	*node_pipeline;

	ft_memset(&parser, 0 ,sizeof(t_parser));
	parser.tkns = tkns;
	parser.curr_tkn = (t_token *) parser.tkns->content;
	parser.errcode = NO_ERR;
	node_pipeline = NULL;
	while (curr_type(parser) != T_NULL)
	{
		if (curr_type(parser) != T_OP_PRT && curr_type(parser) != T_WORD)
		{
			ft_dprintf(0, "{1;33}An error occured while parsing, invalid start token : %s{0}\n",
					get_type(cast_tkn(parser.tkns)->type));
			return (NULL);
		}
		while (curr_type(parser) == T_OP_PRT)
		{
			push_stack(&parser.op_stack, cast_tkn(parser.tkns));
			consume_token(&parser);
		}
		if (curr_type(parser) != T_CL_PRT && curr_type(parser)!= T_NULL)
		{
			node_pipeline = retrieve_pipeline(&parser);
			if (!node_pipeline)
			{
				ft_dprintf(0, "{1;33}An error occured while parsing : bad pipeline.{0}\n");
				return (NULL);
			}
			else
			{
				push_stack(&parser.output_stack, node_pipeline);
				update_tkns(&parser);
			}
		}
		while (curr_type(parser) == T_CL_PRT)
		{
			if (is_top_an_operator(parser))
			{
				create_node(&parser.output_stack, cast_tkn(parser.op_stack.top)->type); 
				pop_stack(&parser.op_stack, NULL, 2);
			}
			else
				pop_stack(&parser.op_stack, NULL, 1);
			consume_token(&parser);
		}
		if (curr_type(parser) == T_LOG_AND || curr_type(parser) == T_LOG_OR)
		{
			if (parser.op_stack.top && is_top_an_operator(parser))
			{
				create_node(&parser.output_stack, cast_tkn(parser.op_stack.top)->type); 
				pop_stack(&parser.op_stack, NULL, 1);
			}
			push_stack(&parser.op_stack, parser.curr_tkn);
			consume_token(&parser);
		}
	}
	if (parser.op_stack.top && is_top_an_operator(parser))
	{
		create_node(&parser.output_stack, cast_tkn(parser.op_stack.top)->type); 
		pop_stack(&parser.op_stack, NULL, 1);
	}
	//ft_printf("Last token used :\n\t< {32}%s{0} > {1}Type{0} <{1;36}%s{0}>",
	//		parser.last_used_tkn->val, get_type(parser.last_used_tkn->type));
	return ((t_ast_tree_node *) parser.output_stack.top->content);
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
