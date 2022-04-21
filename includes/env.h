/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:16:18 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:20:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "ast.h"
# include <stdbool.h>

typedef struct s_var
{
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	value_len;
	bool	return_value;
}	t_var;

typedef struct s_minishell
{
	char			*cmd_str;
	t_dlist			*vars;
	int				err;
	int				last_ret;
	int				save_stdin;
	t_ast_tree_node	*root;
	void			*current_pipeline_first;
	bool			ambiguous_redir;
}	t_minishell;

/* var.c */

t_dlist	*add_var(t_dlist **lst_var, char *name, char *value);
void	del_var(t_dlist **lst_var, char *name);
t_dlist	*import_var(t_minishell *minishell, char **envp);
void	free_var(void *dlst_content);
void	free_env(t_dlist *env);

/* var_utils.c */

t_var	*update_var(t_dlist *lst_var, char *name, t_var to_update);
t_var	*get_var(t_dlist *lst_var, char *name);
t_dlist	*import_one_var(t_dlist **lst_var, char *value);

/* env.c */

int		refill_env(t_dlist **env);
int		get_current_working_dir(char **cwd);
char	**export_env(t_dlist *lst);

#endif
