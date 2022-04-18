/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/18 02:44:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include "minishell.h"

/* match_pattern() returns true if filename is respecting the pattern, else
 * , it returns false.
 * The algorithm is both iterative and recursive.
 * is_a_intrp_wildcard() here checks if the wildcard is interpretable :
 * interpretable means that the wildcard wasn't quoted.
 * */

static bool	match_pattern(t_arg *arg, char *filename, char *pattern)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (pattern[j] != '\0')
	{
		if (pattern[j] == '*' && is_intrp_wldc(arg->wldc_lst, &pattern[j]))
			break ;
		if (filename[i++] != pattern[j++])
			return (false);
	}
	if (filename[i] == '\0' && pattern[j] == '\0')
		return (true);
	else if (filename[i] != '\0' && pattern[j] == '\0')
		return (false);
	while (pattern[j + 1] == '*')
		j++;
	if (pattern[j + 1] == '\0')
		return (true);
	while (filename[i] && filename[i] != pattern[j + 1])
		i++;
	if (filename[i] == '\0')
		return (false);
	return (match_pattern(arg, &filename[i], &pattern[j + 1]));
}

/* new_file_elem() creates a new double linked list element from a dirent
 * pointer.
 * Malloc tkn, elem, filename_dup. */

static t_dlist	*new_file_elem(struct dirent *dir_ent)
{
	t_arg	*arg;
	t_dlist	*elem;

	arg = new_arg(dir_ent->d_name, T_WORD, true);
	if (!arg)
		return (NULL);
	elem = ft_dlstnew((void *) arg);
	if (!elem)
	{
		free_arg(arg);
		return (NULL);
	}
	return (elem);
}

/* add_file_to_list() check if the current file is matching the token value
 * (the pattern).
 * If so, a duplicate of the filename is perform and a new element is added to
 * the double linked list files.
 * If not, the function return.
 * If any allocation error occurs, it returns -1. */

int	add_file_to_list(t_arg *arg, t_dlist **files, struct dirent *dir_ent)
{
	t_dlist	*elem;

	if (dir_ent->d_type != DT_UNKNOWN && dir_ent->d_name[0] != '.')
	{
		if (match_pattern(arg, dir_ent->d_name, arg->value) == true)
		{
			elem = new_file_elem(dir_ent);
			if (!elem)
				return (-1);
			ft_dlstadd_back(files, elem);
		}
	}
	return (0);
}

/* ascii_sort_list() sorts the list in ascii order (ignoring case !)
 * using insert sort algorithm, so that the minishell behave like bash. */

void	ascii_sort_list(t_dlist *files)
{
	char	*curr_filename;

	files = files->next;
	while (files)
	{
		curr_filename = files->content;
		while (files->prev != NULL
			&& ft_strcmp_ignore_case (files->prev->content, curr_filename) > 0)
		{
			files->content = files->prev->content;
			files = files->prev;
		}
		files->content = curr_filename;
		files = files->next;
	}
}
