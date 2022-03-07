/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:55:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/07 18:08:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum	s_node_type
{
	NODE_WORD,
	NODE_COMMAND,
	NODE_EMPTY_COMMAND,
	NODE_PIPE,
	NODE_IO,
	NODE_RD_OUT,
	NODE_RD_IN,
	NODE_RD_HERE
}	t_node_type;

typedef struct	s_ast_tree_node
{
	t_node_type				type;
	char					*value;
	struct s_ast_tree_node	*left;
	struct s_ast_tree_node	*right;
}	t_ast_tree_node;

t_ast_tree_node	*ast_tree_create_node(char *value, t_node_type type);
void			ast_tree_delete_node(t_ast_tree_node *node);
t_ast_tree_node	*ast_tree_attach(t_ast_tree_node *root, t_ast_tree_node *left,
		t_ast_tree_node *right);

#endif
