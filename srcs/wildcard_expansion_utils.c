/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/04 16:41:46 by plouvel          ###   ########.fr       */
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

bool	handle_quote(char *filename, char *pattern, size_t *pi, size_t *pj)
{
	size_t	i;
	size_t	j;
	char	quote;
	bool	match;

	i = *pi;
	j = *pj;
	quote = pattern[j++];
	match = true;
	while (pattern[j] != quote && match)
	{
		if (filename[i++] != pattern[j++])
			match = false;
	}
	*pi = i;
	*pj = j++;
	return (match);
}

static bool	match_pattern(t_token *tkn, char *filename, char *pattern)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (pattern[j] != '\0')
	{
		if (pattern[j] == '*' && is_intrp_char(tkn->wldc_list, &pattern[j]))
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
	return (match_pattern(tkn, &filename[i], &pattern[j + 1]));
}

/* new_file_elem() creates a new double linked list element from a dirent
 * pointer.
 * Malloc tkn, elem, filename_dup. */

static t_dlist	*new_file_elem(struct dirent *dir_ent)
{
	t_token	*tkn;
	t_dlist	*elem;
	char	*filename_dup;

	filename_dup = ft_strdup(dir_ent->d_name);
	if (!filename_dup)
		return (NULL);
	tkn = new_token(filename_dup, ft_strlen(filename_dup), T_WORD);
	if (!tkn)
	{
		free(filename_dup);
		return (NULL);
	}
	elem = ft_dlstnew((void *) tkn);
	if (!elem)
	{
		free_token(tkn);
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

int	add_file_to_list(t_token *tkn, t_dlist **files, struct dirent *dir_ent)
{
	t_dlist	*elem;

	if (dir_ent->d_type != DT_UNKNOWN && dir_ent->d_name[0] != '.')
	{
		if (match_pattern(tkn, dir_ent->d_name, tkn->val) == true)
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
				&& ft_strcmp_ignore_case
				(files->prev->content, curr_filename) > 0)
		{
			files->content = files->prev->content;
			files = files->prev;
		}
		files->content = curr_filename;
		files = files->next;
	}
}
