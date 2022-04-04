/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/04 11:32:32 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

t_dlist	*import_one_var(t_dlist **lst_var, char *value);
t_dlist	*import_empty_var(t_dlist **lst_var, char *name);
void free_env(t_dlist *env);

void set_signals_as_prompt();
void set_signals_as_here_doc();
void set_signals_as_parent();
#endif
