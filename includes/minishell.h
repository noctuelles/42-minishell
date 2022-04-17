/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/17 14:56:24 by dhubleur         ###   ########.fr       */
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
# include "env.h"

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RST "\e[0m"

# define STR_PROMPT_ARROW       " > "
# define STR_STD_PROMPT          "minishell" STR_PROMPT_ARROW
# define STR_PARSE_ERROR        "minishell : %s: near token '%s'.\n"
# define STR_ERROR              "minishell : %s.\n"
# define STR_ERROR_M            "minishell : %s: %s.\n"
# define STR_MALLOC             "malloc"
# define STR_OPENDIR            "opendir"
# define STR_READDIR            "readdir"
# define STR_GETCWD             "readdir"
# define CURRENT_DIR            "."

# define ENO                    0

# define STR_BUILTIN_EXPORT     "export"

void	*display_error_more(const char *fcnt_name);

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



/* wildcard_expansion.c */

void	print_tokens(void *content);
t_dlist	*wildcard_expansion(t_dlist **args, t_dlist *elem, t_arg *arg);

/* wildcard_expansion_utils.c */

int	add_file_to_list(t_arg *arg, t_dlist **files, struct dirent *dir_ent);
void	ascii_sort_list(t_dlist *files);
size_t	compute_str_size(t_dlist *files);

/* var_expansion.c */

t_dlist	*var_expansion(t_dlist **args, t_dlist *elem,
		t_arg *arg, t_dlist *env_var);

/* var_expansion_utils.c */

t_var	get_var_info(char *str, t_dlist *env_var);
ssize_t	include_variable(t_arg *arg, t_var var);

/* var_expansion_post.c */

t_dlist	*tokenize_from_arg(t_arg *old_arg, char *str);

/* var_expansion_post_utils.c */

t_arg	*add_to_args_cpy(t_lexer *lex, t_arg *old_arg);
void	update_prev(t_lexer *lex);
void	check_for_break(t_lexer *lex);

#endif
