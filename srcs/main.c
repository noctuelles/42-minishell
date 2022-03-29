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


	lst = import_var(&lst, envp);
	while (1)
	{
		size_t	i = 0;
		char *str = readline("> ");
		add_history(str);
		lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
		if (!lexer)
			return (1);

		ret_code = fill_lexer_from_str(lexer, str);
		print_tokens(*lexer);
		while (i < lexer->idx - 1)
		{
			tkn = &lexer->tkns[i];
			var_expansion(tkn, lst);
			if (tkn->wldc_list)
			{
				for (t_list *list = tkn->wldc_list; list; list = list->next)
				{
					printf("wildcard at %p : %s\n", list->content,(char *) list->content);
				}
			}
			wildcard_expansion(tkn);
			i++;
		}
		puts("\nAfter expansion :\n");
		print_tokens(*lexer);
		free_lexer(lexer);
	}
	ft_dlstclear(&lst, free_var);
	return (0);
}
