/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:08:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/04 17:36:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_token	set_token(t_token *tkn, char *val, size_t len,
														t_token_type type)
{
	tkn->val = val;
	tkn->len = len;
	tkn->type = type;
	return (*tkn);
}

t_token	search_existing_token(const char *str)
{
	t_token	token;

	if (ft_strncmp(str, STR_LOG_OR, 2) == 0)
		return (set_token(&token, STR_LOG_OR, 2, T_LOG_OR));
	else if (ft_strncmp(str, STR_LOG_AND, 2) == 0)
		return (set_token(&token, STR_LOG_AND, 2, T_LOG_AND));
	else if (ft_strncmp(str, STR_RD_FILE_APN, 2) == 0)
		return (set_token(&token, STR_RD_FILE_APN, 2, T_REDIR));
	else if (ft_strncmp(str, STR_RD_STDIN_HEREDOC, 2) == 0)
		return (set_token(&token, STR_RD_STDIN_HEREDOC, 2, T_REDIR));
	else if (ft_strncmp(str, STR_PIPE, 1) == 0)
		return (set_token(&token, STR_PIPE, 1, T_PIPE));
	else if (ft_strncmp(str, STR_RD_FILE, 1) == 0)
		return (set_token(&token, STR_RD_FILE, 1, T_REDIR));
	else if (ft_strncmp(str, STR_RD_STDIN, 1) == 0)
		return (set_token(&token, STR_RD_STDIN, 1, T_REDIR));
	else if (ft_strncmp(str, STR_OP_PRT, 1) == 0)
		return (set_token(&token, STR_OP_PRT, 1, T_OP_PRT));
	else if (ft_strncmp(str, STR_CL_PRT, 1) == 0)
		return (set_token(&token, STR_CL_PRT, 1, T_CL_PRT));
	else if (ft_strncmp(str, STR_SP, 1) == 0)
		return (set_token(&token, STR_SP, 1, T_BREAK));
	return (set_token(&token, NULL, 0, T_NULL));
}

void	*set_lexer_errcode(t_lexer *lexer, int errcode)
{
	lexer->errcode = errcode;
	return (NULL);
}
