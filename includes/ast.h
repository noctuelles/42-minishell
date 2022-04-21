/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:55:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/21 16:26:56 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"

/******************************************************************************
 *                              Typedef & Enum                                *
 *****************************************************************************/

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_COMMAND,
	NODE_EMPTY_COMMAND,
	NODE_LOGICAL_AND,
	NODE_LOGICAL_OR,
}	t_node_type;

typedef struct s_ast_tree_node
{
	t_node_type				type;
	t_dlist					*args;
	struct s_ast_tree_node	*left;
	struct s_ast_tree_node	*right;
}	t_ast_tree_node;

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

/* ast.c */

t_ast_tree_node	*ast_tree_create_node(t_dlist *args, t_node_type type);
void			ast_tree_apply_preorder(t_ast_tree_node *root);
void			ast_tree_print_graph(t_ast_tree_node *root);
void			ast_tree_delete_node(void *node);
t_ast_tree_node	*ast_tree_attach(t_ast_tree_node *root, t_ast_tree_node *left,
					t_ast_tree_node *right);

/* Debug purpose. */

/*void	ast_print_tree(char *prefix, t_ast_tree_node *node, bool is_left);*/

#endif
