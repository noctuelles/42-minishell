/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/12 17:07:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include "lexer.h"
# include "parser.h"
# include <errno.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RST "\e[0m"

# define SHELL_NAME             "minishell"

# define STR_PARSE_ERROR        SHELL_NAME ": %s: near token '%s'.\n"
# define STR_ERROR              SHELL_NAME ": %s.\n"
# define STR_ERROR_M            SHELL_NAME ": %s: %s.\n"
# define STR_MALLOC             "malloc"
# define STR_OPENDIR            "opendir"
# define STR_READDIR            "readdir"
# define CURRENT_DIR            "."

# define ENO                    0

# define STR_BUILTIN_EXPORT     "export"

/* struct s_var:
 *
 *    name     : the name of the variable.
 *    value    : the value of the variable.
 *    name_len : the lenght of the variable name.
 *    value_len: the lenght of the variable value.
 *    inherit  : inherit from the execution environnement of the shell.
 *    env_var  : if it's a environnement variable, thus, exported when
 *               executing a program with the minishell.
 */

typedef struct s_var
{
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	value_len;
	t_bool	inherit;
}	t_var;

/* struct s_minishell:
 *
 *    ## ENVIRONNEMENT & VARIABLES ##
 *
 *    vars        : linked list containing shell and environnement variable.
 *    envp        : char ** mean to be passed to exec() family function.
 *    update_envp : if envp need to be updated, this variable should be TRUE.
 */

typedef struct s_minishell
{
	t_dlist	*vars;
	char	**envp;
	t_bool	update_envp;
	int		last_ret;
}	t_minishell;

/* var.c */

t_var	*get_var(t_dlist *lst_var, char *name);
t_dlist	*add_var(t_dlist **lst_var, t_var add_var);
void	del_var(t_dlist **lst_var, char *name);
void	free_var(void *dlst_content);
t_dlist	*import_var(t_dlist **lst_var, char **envp);

/* var_utils.c */

t_var	*update_var(t_dlist *lst_var, char *name, t_var to_update);

/* env.c */

char	**export_env(t_dlist *lst);

t_dlist	*import_one_var(t_dlist **lst_var, char *value);
t_dlist	*import_empty_var(t_dlist **lst_var, char *name);
void free_env(t_dlist *env);

void set_signals_as_prompt();
void set_signals_as_here_doc();
void set_signals_as_parent();
/* io_utils.c */

void	print_minishell_exception(const char *submsg, const char *msg);
char	*get_parser_error(t_parser_errcode errcode);
char	*get_lexer_error(t_lexer_errcode errcode);

/* linked_list_utils.c */

t_list	*is_intrp_wldc(t_list *lst, char *c);
bool	is_expnd_quote(t_list *lst, char *pquote);
bool	is_rem_quote(t_list *lst, char *pquote);
t_list	*add_to_list(t_list **list, void *content);
t_dlist	*insert_list(t_dlist **main_lst, t_dlist *to_insert, t_dlist *elem);

/*******************************************************************************
 *                              Expansion files                                *
 ******************************************************************************/

/* wildcard_expansion.c */

void	print_tokens(void *content);
t_dlist	*wildcard_expansion(t_dlist **tkns, t_dlist *elem, t_token *tkn);

/* wildcard_expansion_utils.c */

int	add_file_to_list(t_token *tkn, t_dlist **files, struct dirent *dir_ent);
void	ascii_sort_list(t_dlist *files);
size_t	compute_str_size(t_dlist *files);

/* var_expansion.c */

t_dlist	*var_expansion(t_dlist **tkns, t_dlist *elem,
		t_token *tkn, t_dlist *env_var);

/* var_expansion_utils.c */

t_var	get_var_info(char *str, t_dlist *env_var);
ssize_t	include_variable(t_token *tkn, t_var var);

/* var_expansion_post.c */

t_dlist	*tokenize_from_tkn(t_token *old_tkn, char *str);

/* var_expansion_post_utils.c */

t_token	*add_to_tkns_cpy(t_lexer *lex, t_token *old_tkn);
void	update_prev(t_lexer *lex);
void	check_for_break(t_lexer *lex);

#endif
