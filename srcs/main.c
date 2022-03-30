#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	print_tokens(void *content)
{
	t_token	*tkn;
	
	tkn = (t_token *) content;
	printf("< %s >\n", tkn->val);
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	t_dlist	*lst;
	t_lexer	*lexer;

	lst = NULL;
	/*
	lst = NULL;
	ast_root = parse(argv[1]);
	if (ast_root)
		ast_tree_delete_node(ast_root);
	*/


	lst = import_var(&lst, envp);
	while (1)
	{
		char *str = readline("\n> ");
		if (!str)
			break ;
		add_history(str);
		lexer = lex_str(str);
		if (lexer)
		{
			printf("\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			printf("\nAfter variable expansion :\n");
			for (t_dlist *elem = lexer->tkns; elem; elem = elem->next)
			{
				t_token *tkn = (t_token *) elem->content;
				if (tkn->type == T_WORD)
					tkn = var_expansion(tkn, lst);
			}
			printf("\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			printf("\nAfter wildcard expansion :\n");
			t_dlist *elem;
			elem = lexer->tkns;
			while (elem)
			{
				t_token *tkn = (t_token *) elem->content;
				if (tkn->type == T_WORD)
					elem = wildcard_expansion(lexer, elem, tkn);
				elem = elem->next;
			}
			printf("\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			free_lexer(lexer);
		}
		free(str);
	}
	return (0);
}
