/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:08:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 17:33:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
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
	else if (ft_strncmp(str, STR_EQUALS, 1) == 0)
		return (set_token(&token, STR_EQUALS, 1, T_EQUALS));
	else if (ft_strncmp(str, STR_SP, 1) == 0)
		return (set_token(&token, STR_SP, 1, T_BREAK));
	return (set_token(&token, NULL, 0, T_NULL));
}

void	*set_lexer_errcode(t_lexer *lexer, int errcode)
{
	lexer->errcode = errcode;
	return (NULL);
}

static void	display_tokens(t_lexer *lexer)
{
	t_token	token;
	size_t	i;

	i = 0;
	while (i < lexer->idx)
	{
		token = lexer->tkns[i++];
		printf("Token value : %s\n"
			   "Token len   : %lu\n"
			   "Token type  : %d\n\n",
			   token.val, token.len, token.type);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer	lexer = {0};
	t_dlist	*lst_var = NULL;

	import_var(&lst_var, envp);
	if (argc == 1)
		return (1);
	if (!fill_lexer_from_str(&lexer, argv[1]))
	{
		puts("Unable to lex your input.");
		if (lexer.errcode == E_MEM)
			puts("Cannot allocate memory.");
		else if (lexer.errcode == E_PRT)
			puts("Parenthesis not closed");
		else if (lexer.errcode == E_QUOTE)
			puts("Quote not closed");
	}
	else
	{
		puts("\nTokens output. -- before expansion \n");
		display_tokens(&lexer);
		puts("\nTokens output. -- after expansion and quote removal \n");
		expand_var_from_tkns(lst_var, &lexer);
		display_tokens(&lexer);
	}
	ft_dlstclear(&lst_var, free_var);
	free_tkns(lexer.tkns, lexer.idx);
	return (0);
}
