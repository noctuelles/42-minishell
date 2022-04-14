/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:57:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/14 16:22:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"

void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode)
{
	parser->errcode = errcode;
	return (NULL);
}

t_bool	match(t_parser *parser, t_token_type type, char **value)
{
	t_token	*tkn;

	if (parser->tkns == NULL)
		return (false);
	tkn = (t_token *) parser->tkns->content;
	parser->last_used_tkn = tkn;
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
