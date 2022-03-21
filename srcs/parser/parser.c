/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:00:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/16 18:31:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

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

void	print_parse_exception(const char *errmsg, const char *precision)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	if (precision != NULL)
	{
		ft_putstr_fd(": near '", STDERR_FILENO);
		ft_putstr_fd(precision, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd(".\n", STDERR_FILENO);
}

static t_lexer	*lex_input(char *str)
{
	t_lexer	*lexer;
	int		ret_code;

	lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	ret_code = fill_lexer_from_str(lexer, str);
	if (ret_code != 0)
	{
		if (ret_code == ERR_MEM)
			perror("minishell");
		else
			print_parse_exception(get_lexer_error(ret_code),
					lexer->tkns[lexer->idx - 1].val);
		free_lexer(lexer);
		lexer = NULL;
	}
	return (lexer);
}

static t_ast_tree_node	*parse_from_lexer(t_lexer *lexer)
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
		// Here we're doing variable expansion and removing all quote.
	}
	return (root);
}

t_ast_tree_node	*parse(char *str)
{
	t_lexer			*lexer;
	t_ast_tree_node	*ast_root;

	lexer = lex_input(str);
	if (!lexer)
		return (NULL);
	ast_root = parse_from_lexer(lexer);
	free_lexer(lexer);
	return (ast_root);
}
