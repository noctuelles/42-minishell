#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_tokens(t_lexer lexer)
{
	for (size_t i = 0; i < lexer.idx; i++)
		printf("< '%s' %d >\n", lexer.tkns[i].val, lexer.tkns[i].type);
}

int main(int argc, char **argv)
{
	(void) argc;
	t_lexer	lexer = {0};
	t_ast_tree_node	*root;

	char *str = argv[1];
	fill_lexer_from_str(&lexer, str);
	print_tokens(lexer);
	root = parse(&lexer);
	(void) root;
	free_lexer(&lexer);
	return (0);
}
