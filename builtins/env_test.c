/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:13:37 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 18:42:11 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "test.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	fill_word(char *word, char *str, int first, int last)
{
	int	i;
	int	j;

	i = -1;
	j = first - 1;
	while (++j < last)
		word[++i] = str[j];
	word[++i] = '\0';
}

char	**ft_split_first(char *str, char sep)
{
	int		first;
	int		second;
	char	**words;

	first = 0;
	while (str[first] && str[first] != sep)
		first++;
	if (!str[first])
		return (NULL);
	second = ft_strlen(str) - first - 1;
	words = malloc(sizeof(char *) * 2);
	if (!words)
		return (NULL);
	words[0] = malloc(sizeof(char) * (first + 1));
	words[1] = malloc(sizeof(char) * (second + 1));
	if (!words[0] || !words[1])
		return (NULL);
	fill_word(words[0], str, 0, first);
	fill_word(words[1], str, first + 1, ft_strlen(str));
	return (words);
}

t_env	*get_env_element(char *env)
{
	t_env	*env_elem;
	char	**words;

	env_elem = malloc(sizeof(t_env));
	if (!env_elem)
		return (NULL);
	words = ft_split_first(env, '=');
	if (!words)
		return (NULL);
	env_elem->next = NULL;
	env_elem->name = words[0];
	env_elem->value = words[1];
	return (env_elem);
}

void	print_env_list(t_env **env_list)
{
	t_env	*elem;

	elem = *env_list;
	while (elem != NULL)
	{
		printf("%s=%s\n", elem->name, elem->value);
		elem = elem->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}


char *get_value(t_env **env_list, char *name)
{
	t_env	*elem;

	elem = *env_list;
	while (elem != NULL)
	{
		if(ft_strcmp(name, elem->name) == 0)
			return elem->value;
		elem = elem->next;
	}
	return NULL;
}

int is_var_with_name(t_env **env_list, char *name)
{
	t_env	*elem;

	elem = *env_list;
	while (elem != NULL)
	{
		if(ft_strcmp(name, elem->name) == 0)
			return 1;
		elem = elem->next;
	}
	return 0;
}

void remove_var(t_env **env_list, char *name)
{
	t_env	*elem;
	
	if(ft_strcmp(name, (*env_list)->name) == 0)
		*env_list = (*env_list)->next;
	else
	{
		elem = *env_list;
		while (elem->next != NULL)
		{
			if(ft_strcmp(name, elem->next->name) == 0)
			{
				elem->next = elem->next->next;
				return ;
			}
			elem = elem->next;
		}
	}
}

void add_var(t_env **env_list, t_env *add_elem)
{
	t_env	*elem;
	
	if(ft_strcmp(add_elem->name, (*env_list)->name) == 0)
	{
		free(*env_list);
		*env_list = add_elem;
	}
	else
	{
		elem = *env_list;
		while (elem->next != NULL)
		{
			if(ft_strcmp(add_elem->name, elem->next->name) == 0)
			{
				free(elem->next);
				elem->next = add_elem;
				return ;
			}
			elem = elem->next;
		}
		elem->next = add_elem;
	}
}

void	env_update(t_env **env, char *name, char *value)
{
	t_env	*elem;

	elem = *env;
	while(elem != NULL)
	{
		if(strcmp(elem->name, name) == 0)
		{
			free(elem->value);
			elem->value = value;
			return ;
		}
		elem = elem->next;
	}
}

t_env *get_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*env;
	t_env	*elem;
	int		i;

	env_list = NULL;
	if (envp[0] == NULL)
	{
		printf("Empty environment\n");
		return NULL;
	}
	else
	{
		i = -1;
		while (envp[++i])
		{
			env = get_env_element(envp[i]);
			if (!env)
				return NULL;
			if (env_list == NULL)
				env_list = env;
			else
			{
				elem = env_list;
				while (elem->next != NULL)
					elem = elem->next;
				elem->next = env;
			}
		}
	}
	return env_list;
}
