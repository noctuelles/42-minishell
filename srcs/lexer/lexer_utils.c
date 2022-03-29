/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:08:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/29 17:06:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_token	set_token(t_token *tkn, char *val, size_t len,
														t_token_type type)
{
	tkn->val = val;
	tkn->len = len;
	tkn->type = type;
	tkn->quote_list = NULL;
	tkn->wldc_list = NULL;
	tkn->quote = '\0';
	return (*tkn);
}

void	free_lexer(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->idx)
	{
		if (lexer->tkns[i].type == T_WORD)
			free(lexer->tkns[i].val);
		i++;
	}
	free(lexer->tkns);
	free(lexer);
}

t_token	search_existing_token(const char *str)
{
	t_token	token;

	if (ft_strncmp(str, STR_LOG_OR, 2) == 0)
		return (set_token(&token, STR_LOG_OR, 2, T_LOG_OR));
	else if (ft_strncmp(str, STR_LOG_AND, 2) == 0)
		return (set_token(&token, STR_LOG_AND, 2, T_LOG_AND));
	else if (ft_strncmp(str, STR_RD_FILE_APN, 2) == 0)
		return (set_token(&token, STR_RD_FILE_APN, 2, T_DGRT));
	else if (ft_strncmp(str, STR_RD_STDIN_HEREDOC, 2) == 0)
		return (set_token(&token, STR_RD_STDIN_HEREDOC, 2, T_DLESS));
	else if (ft_strncmp(str, STR_PIPE, 1) == 0)
		return (set_token(&token, STR_PIPE, 1, T_PIPE));
	else if (ft_strncmp(str, STR_RD_FILE, 1) == 0)
		return (set_token(&token, STR_RD_FILE, 1, T_GRT));
	else if (ft_strncmp(str, STR_RD_STDIN, 1) == 0)
		return (set_token(&token, STR_RD_STDIN, 1, T_LESS));
	else if (ft_strncmp(str, STR_OP_PRT, 1) == 0)
		return (set_token(&token, STR_OP_PRT, 1, T_OP_PRT));
	else if (ft_strncmp(str, STR_CL_PRT, 1) == 0)
		return (set_token(&token, STR_CL_PRT, 1, T_CL_PRT));
	else if (ft_strncmp(str, STR_SP, 1) == 0)
		return (set_token(&token, STR_SP, 1, T_BREAK));
	return (set_token(&token, NULL, 0, T_NULL));
}
