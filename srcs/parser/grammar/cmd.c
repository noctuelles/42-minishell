/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:10:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/11 16:38:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

t_ast_tree_node	*CMD(t_parser *parser)
{

}

t_ast_tree_node	*CMD1(t_parser *parser)
{
	return (SIMPLE_CMD(parser));
}

t_ast_tree_node	*CMD2(t_parser *parser)
{

}
