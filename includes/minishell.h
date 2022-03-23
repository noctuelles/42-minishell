/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/23 23:05:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H

# include <sys/types.h>
# include <stdbool.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

# define SHELL_NAME             "minishell"

# define STR_PARSE_ERROR        SHELL_NAME ": %s: near token '%s'.\n"
# define STR_ERROR              SHELL_NAME ": %s.\n"
# define STR_ERROR_M            SHELL_NAME ": %s: %s.\n"
# define STR_MALLOC             "malloc"
# define STR_OPENDIR            "opendir"
# define STR_READDIR            "readdir"
# define CURRENT_DIR            "."

# define ENO                    0

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

/* io_utils.c */

void	print_minishell_exception(const char *submsg, const char *msg);
char	*get_parser_error(t_parser_errcode errcode);
char	*get_lexer_error(t_lexer_errcode errcode);

/*******************************************************************************
 *                              Expansion files                                *
 ******************************************************************************/

/* wildcard_expansion.c */

char	*wildcard_expansion(t_token *tkn);

/* wildcard_expansion_utils.c */

int	add_file_to_list(t_dlist **files, char *filename, char *pattern,
		unsigned char d_type, t_token *tkn);
void	ascii_sort_list(t_dlist *files);
size_t	compute_str_size(t_dlist *files);

/* var_expansion.c */

t_token	*var_expansion(t_token *tkn, t_dlist *env_var);

/* var_expansion_utils.c */

t_var	get_var_info(char *str, t_dlist *env_var);
ssize_t	include_variable(t_token *tkn, char **str, t_var var);
bool	is_an_expanded_quote(t_list *quote_list, size_t i_quote);

#endif
