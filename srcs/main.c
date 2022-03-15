#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	print_tokens(t_lexer lexer)
{
	for (size_t i = 0; i < lexer.idx; i++)
		printf("< '%s' %d >\n", lexer.tkns[i].val, lexer.tkns[i].type);
}

t_lexer	*lex_input(char *str)
{
	t_lexer	*lexer;
	int		ret_code;

	lexer = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	ret_code = fill_lexer_from_str(lexer, str);
	if (ret_code != 0)
	{
		if (ret_code == ERR_MEM)
			perror("minishell");
		else
			print_parse_exception(get_lexer_error(ret_code),
					lexer->tkns[lexer->idx - 1].val);
		free_lexer(lexer);
		lexer = NULL;
	}
	return (lexer);
}

int main(int argc, char **argv)
{
	(void) argc;
	t_lexer	*lexer;
	t_ast_tree_node	*root;

	lexer = lex_input(argv[1]);
	if (!lexer)
		return (1);
	print_tokens(*lexer);
	root = parse_from_lexer(lexer);
	(void) root;
	free_lexer(lexer);
	return (0);
}
