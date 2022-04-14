/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushnstack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:15:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 19:38:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static bool	is_top_an_operator(t_parser parser)
{
	t_token	*top_tkn;

	top_tkn = parser.op_stack.top->content;
	if (top_tkn->type == T_LOG_AND || top_tkn->type == T_LOG_OR)
		return (true);
	else
		return (false);
}

static t_ast_tree_node	*create_node(t_parser *parser, t_token_type type)
{
	t_ast_tree_node	*left;
	t_ast_tree_node	*right;
	t_ast_tree_node	*result;
	t_node_type		node_type;

	if (parser->output_stack.top->prev == NULL)
		return (set_parser_errcode(parser, ERR_EXPECTED_COMMAND));
	left = (t_ast_tree_node *) parser->output_stack.top->prev->content;
	right = (t_ast_tree_node *) parser->output_stack.top->content;
	if (type == T_LOG_AND)
		node_type = NODE_LOGICAL_AND;
	if (type == T_LOG_OR)
		node_type = NODE_LOGICAL_OR;
	result = ast_tree_create_node(NULL, node_type);
	if (!result)
		return (set_parser_errcode(parser, ERR_MALLOC));
	ast_tree_attach(result, left, right);
	pop_stack(&parser->output_stack, NULL, 2);
	if (push_stack(parser, &parser->output_stack, result) == NULL)
		return (set_parser_errcode(parser, ERR_MALLOC));
	return (result);
}

int	assemble_out_stack_top(t_parser *parser, size_t npop_op, bool force_pop)
{
	if (parser->op_stack.top && is_top_an_operator(*parser))
	{
		if (create_node(parser, cast_tkn(parser->op_stack.top)->type) == NULL)
			return (-1);
		pop_stack(&parser->op_stack, NULL, npop_op);
	}
	else if (force_pop)
		pop_stack(&parser->op_stack, NULL, 1);
	return (0);
}

int	handle_cmd_start(t_parser *parser)
{
	t_ast_tree_node	*node_pipeline;

	while (curr_type(*parser) == T_OP_PRT)
	{
		push_stack(parser, &parser->op_stack, cast_tkn(parser->tkns));
		consume_token(parser);
	}
	if (curr_type(*parser) != T_CL_PRT && curr_type(*parser) != T_NULL)
	{
		node_pipeline = pipeline(parser);
		if (!node_pipeline)
			return (-1);
		else
			push_stack(parser, &parser->output_stack, node_pipeline);
	}
	return (0);
}

int	handle_cmd_end(t_parser *parser)
{
	while (curr_type(*parser) == T_CL_PRT)
	{
		if (assemble_out_stack_top(parser, 2, true) == -1)
			return (-1);
		consume_token(parser);
	}
	if (curr_type(*parser) == T_LOG_AND || curr_type(*parser) == T_LOG_OR)
	{
		if (assemble_out_stack_top(parser, 1, false) == -1)
			return (-1);
		push_stack(parser, &parser->op_stack, parser->curr_tkn);
		consume_token(parser);
	}
	return (0);
}
