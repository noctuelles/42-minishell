/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:57:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 17:16:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

t_bool	match(t_parser *parser, t_token_type type, char **value)
{
	if (parser->lex_idx >= parser->lexer->idx)
		return (FALSE);
	if (parser->lexer->tkns[parser->lex_idx].type == type)
	{
		if (value != NULL)
				*value = parser->lexer->tkns[parser->lex_idx].val;
		parser->lex_idx += 1;
		return (TRUE);
	}
	parser->lex_idx += 1;
	return (FALSE);
}

/* call_production() call a production rule, saving the index in the current
 * to be restore upon completion of the rule if restore is set to TRUE.  */

t_ast_tree_node	*call_production(t_parser *parser,
		t_ast_tree_node *(*fprod)(t_parser *), t_ast_tree_node **root,
		size_t save)
{
	parser->lex_idx = save;
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
	if (errcode != NO_ERR)
		parser->errcode = errcode;
	return (NULL);
}

char	*get_parse_error(t_parser_errcode errcode)
{
	if (errcode == ERR_UNEXCEPTED_IO_TOKEN)
		return ("excepted filename for redirection");
	else if (errcode == ERR_UNEXCEPTED_IO_HEREDOC_TOKEN)
		return ("excepted here-doc delimiter");
	else if (errcode == ERR_UNEXCEPTED_EOF)
		return ("unexcepted end-of-file or token");
	else if (errcode == ERR_EXCEPTED_COMMAND)
		return ("excepted command");
	else
		return ("syntax error");
}
