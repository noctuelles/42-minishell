#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf.h"
#include <unistd.h>

bool DEBUG = true;

char *get_type(t_token_type type)
{
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_LOG_AND)
		return ("T_LOG_AND");
	if (type == T_LOG_OR)
		return ("T_LOG_OR");
	if (type == T_LESS)
		return ("T_LESS");
	if (type == T_DLESS)
		return ("T_DLESS");
	if (type == T_GRT)
		return ("T_GRT");
	if (type == T_DGRT)
		return ("T_DGRT");
	if (type == T_OP_PRT)
		return ("T_OP_PRT");
	if (type == T_CL_PRT)
		return ("T_CL_PRT");
	if (type == T_WORD)
		return ("T_WORD");
	return ("T_NULL");
}

void	print_tokens(void *content)
{
	t_token	*tkn;
	
	tkn = (t_token *) content;
	ft_printf("\t< {32}%s{0} > {1}Type{0} <{1;36}%s{0}>", tkn->val, get_type(tkn->type));
	ft_putchar('\n');
}

void	print_args(void *content)
{
	t_arg	*arg;
	
	arg = (t_arg *) content;
	ft_printf("\t< {32}%s{0} >", arg->value);
	ft_printf(" {4;1}Wildcards{0} :");
	if (arg->wldc_lst)
	{
		ft_putstr("\n\n");
		for (t_list *lst = arg->wldc_lst; lst != NULL; lst = lst->next)
		{
			ft_printf("\t\t| {33}%p{0} : {34}'%c'{0} : ",
					lst->content, * (char *) lst->content);
			ft_putchar('"');
			for (size_t i = 0; arg->value[i]; i++)
			{
				if (&arg->value[i] == (char *) lst->content)
					ft_printf("{1;91}%c{0}", arg->value[i]);
				else
					ft_printf("{1;37}%c{0}", arg->value[i]);
			}
			ft_putstr("\"\n");
		}
	}
	else
		ft_printf("\n\n\t\t| {31}None.{0}\n");
	ft_putchar('\n');
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_dlist	*env_var;
	t_dlist	*tkns;
	t_ast_tree_node *root;

	env_var = NULL;
	env_var = import_var(&env_var, envp);
	while (1)
	{
		char *str = readline("\n" "\e[1;97m" "prompt> " "\e[0m");
		if (!str)
			break ;
		add_history(str);
		if (ft_strcmp(str, "debug") == 0)
		{
			if (!DEBUG)
			{
				ft_printf("\n{1;4}Switching to expansion debug mode.{0}\n");
				DEBUG = true;
			}
			else
			{
				ft_printf("\n{1;4}Switching to normal mode.{0}\n");
				DEBUG = false;
			}
		}
		else
		{
			if (DEBUG)
			{
				root = parse_from_str(str);
				if (root)
				{
					ft_printf("\n{1;4;33}Initial tree :{0}\n\n");
					ast_print_tree("", root, false);
					t_dlist	*elem = root->args;
					while (elem)
					{
						t_arg *arg = elem->content;
						elem = var_expansion(&root->args, elem, arg, env_var);
						if (elem)
							elem = elem->next;
						else
							break ;
					}
					ast_tree_delete_node(root);
					/*if (root)
					{
						ft_printf("\n{1;4;33}After variable expansion :{0}\n\n");
						for (t_dlist *elem = root->args; elem; elem = elem->next)
						{
							t_arg *arg = (t_arg *) elem->content;
							elem = var_expansion(&root->args, elem, arg, env_var);
						}
						printf("\n");
						ft_dlstiter(root->args, print_args);
						ft_printf("\n{1;4;33}After wildcard expansion :{0}\n");
						for (t_dlist *elem = root->args; elem; elem = elem->next)
						{
							t_arg *arg = (t_arg *) elem->content;
							elem = wildcard_expansion(&root->args, elem, arg);
						}
						printf("\n");
						ft_dlstiter(root->args, print_args);
						ft_dlstclear(&tkns, free_token);
					}*/
				}
			}
			else
			{
				tkns = lex_str(str);
				if (tkns)
				{
					ft_printf("\n{1;4;33}Token(s) :{0}\n\n");
					ft_dlstiter(tkns, print_tokens);
				}
			}
		}
		free(str);
	}
	ft_dlstclear(&env_var, free_var);
	return (0);
}
