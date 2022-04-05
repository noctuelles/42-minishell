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
	if (tkn->type == T_WORD)
	{
		ft_printf(" {4;1}Wildcards{0} :");
		if (tkn->wldc_lst)
		{
			ft_putstr("\n\n");
			for (t_list *lst = tkn->wldc_lst; lst != NULL; lst = lst->next)
			{
				ft_printf("\t\t| {33}%p{0} : {34}'%c'{0} : ",
						lst->content, * (char *) lst->content);
				ft_putchar('"');
				for (size_t i = 0; tkn->val[i]; i++)
				{
					if (&tkn->val[i] == (char *) lst->content)
						ft_printf("{1;91}%c{0}", tkn->val[i]);
					else
						ft_printf("{1;37}%c{0}", tkn->val[i]);
				}
				ft_putstr("\"\n");
			}
		}
		else
			ft_printf("\n\n\t\t| {31}None.{0}\n");
	}
	else
		ft_putchar('\n');
	ft_putchar('\n');
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_dlist	*lst;
	t_lexer	*lexer;

	lst = NULL;
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
			ft_printf("\n{1;4;33}Initial token(s) :{0}\n\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			ft_printf("\n{1;4;33}After variable expansion :{0}\n\n");
			for (t_dlist *elem = lexer->tkns; elem; elem = elem->next)
			{
				t_token *tkn = (t_token *) elem->content;
				if (tkn->type == T_WORD)
					elem = var_expansion(&lexer->tkns, elem, tkn, lst);
			}
			printf("\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			ft_printf("\n{1;4;33}After wildcard expansion :{0}\n");
			t_dlist *elem;
			elem = lexer->tkns;
			while (elem)
			{
				t_token *tkn = (t_token *) elem->content;
				if (tkn->type == T_WORD)
					elem = wildcard_expansion(&lexer->tkns, elem, tkn);
				elem = elem->next;
			}
			printf("\n");
			ft_dlstiter(lexer->tkns, print_tokens);
			free_lexer(lexer);
		}
		free(str);
	}
	ft_dlstclear(&lst, free_var);
	return (0);
}
