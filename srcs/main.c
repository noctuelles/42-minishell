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

int main(int argc, char **argv)
{
	(void) argc;
	t_ast_tree_node	*ast_root;

	ast_root = parse(argv[1]);
	if (ast_root)
		ast_tree_delete_node(ast_root);
	else
		return (1);
	return (0);
}
