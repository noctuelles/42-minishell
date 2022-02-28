/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/28 18:08:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H

# include "libft.h"

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
	t_bool	env_var;
}	t_var;

/* var.c */

t_var	*get_var(t_dlist *lst_var, char *name);
t_dlist	*add_var(t_dlist **lst_var, t_var add_var);
void	del_var(t_dlist **lst_var, char *name);
void	free_var(void *dlst_content);
t_dlist	*import_var(t_dlist **lst_var, char **envp);

#endif
