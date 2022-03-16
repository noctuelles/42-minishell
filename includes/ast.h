/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:55:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/15 22:53:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "libft.h"

typedef enum	s_node_type
{
	NODE_PIPE,
	NODE_COMMAND_SUBSHELL,
	NODE_COMMAND,
	NODE_PRIORITY_AND,
	NODE_PRIORITY_OR,
	NODE_LOGICAL_AND,
	NODE_LOGICAL_OR,
	NODE_EMPTY_COMMAND,
	NODE_IO_LIST,
	NODE_COMMAND_SUFFIX,
	NODE_IO_REDIRECT_STDIN,
	NODE_IO_REDIRECT_FILE,
	NODE_IO_REDIRECT_FILE_APPEND,
	NODE_IO_REDIRECT_HERE_DOC,
}	t_node_type;

typedef struct	s_ast_tree_node
{
	t_node_type				type;
	char					*value;
	struct s_ast_tree_node	*left;
	struct s_ast_tree_node	*right;
}	t_ast_tree_node;

t_ast_tree_node	*ast_tree_create_node(char *value, t_node_type type);
void	ast_tree_apply_preorder(t_ast_tree_node *root);
void	ast_tree_print_graph(t_ast_tree_node *root);
void			ast_tree_delete_node(t_ast_tree_node *node);
t_ast_tree_node	*ast_tree_attach(t_ast_tree_node *root, t_ast_tree_node *left,
		t_ast_tree_node *right);

#endif
