/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:00:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 17:04:44 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <string.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

void	fill_word(char *word, char *str, int first, int last);
char	**ft_split_first(char *str, char sep);
t_env	*get_env_element(char *env);
void	print_env_list(t_env **env_list);
char *get_value(t_env **env_list, char *name);
t_env *get_env_list(char **envp);
int is_var_with_name(t_env **env_list, char *name);
void remove_var(t_env **env_list, char *name);
void add_var(t_env **env_list, t_env *elem);

#endif