/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/16 10:46:19 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

t_bool	is_expandable(t_node_type type)
{
	if (type == NODE_IO_REDIRECT_STDIN
			|| type == NODE_IO_REDIRECT_FILE
			|| type == NODE_IO_REDIRECT_FILE_APPEND
			|| type == NODE_COMMAND
			|| type == NODE_COMMAND_SUFFIX)
		return (TRUE);
	else
		return (FALSE);
}


void	expand_tree_value(t_dlist *env_var, t_ast_tree_node *root)
{
	if (root->left != NULL)
		expand_tree_value(env_var, root->left);
	if (root->right != NULL)
		expand_tree_value(env_var, root->right);
	if (is_expandable(root->type)) 
	{
		// Expand the current variable.
	}
	else if (root->type == NODE_IO_REDIRECT_HERE_DOC)
	{
		// Just doing some quote removal.
	}
}

t_ast_tree_node	*parse_from_lexer(t_lexer *lexer)
{
	t_parser		parser;
	t_ast_tree_node	*root;

	parser.lexer = lexer;
	parser.lex_idx = 0;
	parser.errcode = NO_ERR;
	root = complete_cmd(&parser);
	if (!root)
	{
		if (parser.errcode == ERR_MALLOC)
			perror("minishell");
		else
			print_parse_exception(get_parse_error(parser.errcode),
				lexer->tkns[parser.lex_idx - 1].val);
	}
	else
	{

	}
	return (root);
}
