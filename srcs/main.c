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

void	print_tokens(t_lexer lexer)
{
	for (size_t i = 0; i < lexer.idx - 1; i++)
	{
		printf("< '%s' %d >\n", lexer.tkns[i].val, lexer.tkns[i].type);
		if (lexer.tkns[i].quote_list)
		{
			printf("\nQuote imported from expansion :\n");
			/*while (lexer.tkns[i].quote_list)
			{
				printf("At position : %lu\n", *(size_t*)lexer.tkns[i].quote_list->content);
				lexer.tkns[i].quote_list = lexer.tkns[i].quote_list->next;
			}*/
			puts("");
		}
	}
}


int main(int argc, char **argv, char **envp)
{
	(void) argc;
	t_dlist	*lst;
	t_lexer	*lexer;
	t_token	*tkn;
	int		ret_code;

	lst = NULL;
	/*
	lst = NULL;
	ast_root = parse(argv[1]);
	if (ast_root)
		ast_tree_delete_node(ast_root);
	*/

	lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (1);
	lst = import_var(&lst, envp);
	while (1)
	{
		char *str = readline("> ");
		add_history(str);

		ret_code = fill_lexer_from_str(lexer, str);
		print_tokens(*lexer);
		tkn = &lexer->tkns[0];
		var_expansion(tkn, lst);
		print_tokens(*lexer);
		tkn->val = wildcard_expansion(tkn);
		if (tkn->val)
			puts(tkn->val);
		else
			puts("no matche.");
	}
	ft_dlstclear(&lst, free_var);
	return (0);
}
