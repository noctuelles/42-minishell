/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/30 11:12:27 by plouvel          ###   ########.fr       */
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

	i = 0;
	j = 0;
	while (pattern[j] != '\0')
	{
		if (pattern[j] == '*'
				&& is_a_intrp_wildcard(tkn->wldc_list, &pattern[j]))
			break ;
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

/* add_file_to_list() check if the current file is matching the token value
 * (the pattern).
 * If so, a duplicate of the filename is perform and a new element is added to
 * the double linked list files.
 * If not, it to nothing.
 * If any allocation error occurs, it returns -1.
 * Malloc filename_dup, elem. */

int	add_file_to_list(t_token *tkn, t_dlist **files, struct dirent *dir_ent)
{
	t_dlist	*elem;
	char	*filename_dup;

	if (dir_ent->d_type != DT_UNKNOWN && dir_ent->d_name[0] != '.')
	{
		if (match_pattern(tkn, dir_ent->d_name, tkn->val) == true)
		{
			filename_dup = ft_strdup(dir_ent->d_name);
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

/* ascii_sort_list() sorts the list in ascii order using insert sort
 * algorithm. */

void	ascii_sort_list(t_dlist *files)
{
	char	*curr_filename;

	files = files->next;
	while (files)
	{
		curr_filename = files->content;
		while (files->prev != NULL
				&& ft_strcmp_ignore_case(files->prev->content, curr_filename) > 0)
		{
			files->content = files->prev->content;
			files = files->prev;
		}
		files->content = curr_filename;
		files = files->next;
	}
}

/* compute_str_size() computes the size needed for the string size of str_size,
 * in list_to_string() function.
 * A basic strlen is done in each element of files, and one is added for the
 * extra spaces / NUL terminating character. */

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
