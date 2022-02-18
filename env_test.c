/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:13:37 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 14:51:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int	ft_strlen(char *str)
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
		printf("%s = %s\n", elem->name, elem->value);
		elem = elem->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_env	*env;
	t_env	*elem;
	int		i;

	env_list = NULL;
	if (envp[0] == NULL)
	{
		printf("Empty environment\n");
		return (1);
	}
	else
	{
		i = -1;
		while (envp[++i])
		{
			env = get_env_element(envp[i]);
			if (!env)
				return (1);
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
	print_env_list(&env_list);
	return (0);
}
