#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	(void) argc;
	t_ast_tree_node	*ast_root;

	ast_root = parse(argv[1]);
	if (ast_root)
		ast_tree_delete_node(ast_root);
	return (0);
}
