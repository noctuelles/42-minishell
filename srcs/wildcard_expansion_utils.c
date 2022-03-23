/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/23 23:05:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include "minishell.h"

/* match_pattern() returns true if filename is respecting the pattern, else
 * , it returns false.
 * The algorithm is both iterative and recursive.
 * */

static bool	match_pattern(t_token *tkn, char *filename, char *pattern)
{
	size_t	i;
	size_t	j;
	bool	inhibit_wildcard;
	char	quote;
	size_t	nbr;

	i = 0;
	j = 0;
	nbr = 0;
	inhibit_wildcard = false;
	quote = 0;
	while (pattern[j] != '\0')
	{
		if (!inhibit_wildcard && pattern[j] == '*')
			break ;
		if (pattern[j] == '\'' || pattern[j] == '"')
		{
			if (inhibit_wildcard && pattern[j] == quote)
			{
				inhibit_wildcard = false;
				quote = 0;
				j++;
				nbr++;
				continue;
			}
			if (!inhibit_wildcard && !is_an_expanded_quote(tkn->quote_list, j))
			{
				inhibit_wildcard = true;
				quote = pattern[j++];
				nbr++;
				continue;
			}
		}
		if (filename[i++] != pattern[j++])
			return (false);
	}
	if (filename[i] == '\0' && pattern[j] == '\0')
		return (true);
	while (pattern[j + 1] == '*')
		j++;
	if (pattern[j + 1] == '\0')
		return (true);
	while (filename[i] && filename[i] != pattern[j + 1])
		i++;
	if (filename[i] == '\0')
		return (false);
	return (match_pattern(tkn, &filename[i], &pattern[j + 1]));
}

int	add_file_to_list(t_dlist **files, char *filename, char *pattern,
		unsigned char d_type, t_token *tkn)
{
	t_dlist	*elem;
	char	*filename_dup;

	if (d_type != DT_UNKNOWN && filename[0] != '.')
	{
		if (match_pattern(tkn, filename, pattern) == true)
		{
			filename_dup = ft_strdup(filename);
			if (!filename_dup)
				return (-1);
			elem = ft_dlstnew((void *) filename_dup);
			if (!elem)
			{
				free(filename_dup);
				return (-1);
			}
			ft_dlstadd_back(files, elem);
		}
	}
	return (0);
}

/* ascii_sort_list() sorts the list in ascii orderfiles using insert sort
 * algorithm. */

void	ascii_sort_list(t_dlist *files)
{
	char	*curr_filename;

	files = files->next;
	while (files)
	{
		curr_filename = files->content;
		while (files->prev != NULL
				&& ft_strcmp(files->prev->content, curr_filename) > 0)
		{
			files->content = files->prev->content;
			files = files->prev;
		}
		files->content = curr_filename;
		files = files->next;
	}
}

size_t	compute_str_size(t_dlist *files)
{
	size_t	str_size;

	str_size = 0;
	while (files)
	{
		str_size += ft_strlen(files->content) + 1;
		files = files->next;
	}
	return (str_size);
}
