#include <stdio.h>
#include "lexer.h"
#include "minishell.h"

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
