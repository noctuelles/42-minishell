/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:57:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/07 12:41:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_bool	match(t_parser *parser, t_token_type type, char **value)
{
	t_token	*tkn;

	if (parser->tkns == NULL)
		return (false);
	tkn = (t_token *) parser->tkns->content;
	if (tkn->type == type)
	{
		if (value != NULL)
		{
				*value = ft_strdup(tkn->val);
				if (!(*value))
				{
					parser->errcode = ERR_MALLOC;
					return (FALSE);
				}
		}
		parser->tkns = parser->tkns->next;
		return (TRUE);
	}
	parser->tkns = parser->tkns->next;
	return (FALSE);
}

/* call_production() call a production rule, saving the index in the current
 * to be restore upon completion of the rule if restore is set to TRUE.  */

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		t_dlist *save)
{
	parser->tkns = save;
	*root = fprod(parser);
	return (*root);
}

t_ast_tree_node	*call_term(t_parser *parser,
		t_ast_tree_node *(fterm)(t_parser *), t_ast_tree_node **root)
{
	*root = fterm(parser);
	return (*root);
}

void	*quit_production(t_parser *parser, t_ast_tree_node *left,
		t_ast_tree_node *right, t_parser_errcode errcode)
{
	if (left != NULL)
		ast_tree_delete_node(left);
	if (right != NULL)
		ast_tree_delete_node(right);
	if (errcode != NO_ERR && parser->errcode != ERR_MALLOC)
		parser->errcode = errcode;
	return (NULL);
}
