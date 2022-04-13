/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:16:18 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 14:13:40 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include <stdlib.h> 
# include <unistd.h>
# include <stdio.h>

# include "libft.h"

typedef struct s_var
{
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	value_len;
	t_bool	inherit;
}	t_var;

typedef struct s_minishell
{
	t_dlist	*vars;
	int		last_ret;
	int		save_stdin;
}	t_minishell;

t_var	*get_var(t_dlist *lst_var, char *name);
t_dlist	*add_var(t_dlist **lst_var, t_var add_var);
void	del_var(t_dlist **lst_var, char *name);
void	free_var(void *dlst_content);
t_dlist	*import_var(t_dlist **lst_var, char **envp);
t_var	*update_var(t_dlist *lst_var, char *name, t_var to_update);
char	**export_env(t_dlist *lst);
t_dlist	*import_one_var(t_dlist **lst_var, char *value);
t_dlist	*import_empty_var(t_dlist **lst_var, char *name);
void	free_env(t_dlist *env);
void	refill_env(t_dlist **env);

#endif