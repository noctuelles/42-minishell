/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:50:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/29 18:38:59 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "ft_dprintf.h"

/* merge_list_content() merge all the value in the double linked list in the
 * string str.
 * Doesn't malloc.*/

static void	merge_list_content(char *str, t_dlist *files)
{
	char	*filename;
	size_t	i;
	size_t	j;

	i = 0;
	while (files)
	{
		j = 0;
		filename = (char *) files->content;
		while (filename[j] != '\0')
			str[i++] = filename[j++];
		if (files->next == NULL)
			str[i] = '\0';
		else
			str[i++] = ' ';
		files = files->next;
	}
}

/* list_to_string() transform the linked list files, into a ascii sorted string
 * of filenames if files isn't NULL.
 * If files is NULL, then the token value is unchanged.
 * Malloc str.*/

static char	*list_to_string(t_token *tkn, t_dlist *files)
{
	size_t	str_size;
	char	*str;

	if (files == NULL)
		return (tkn->val);
	ascii_sort_list(files);
	str_size = compute_str_size(files);
	str = (char *) malloc(str_size * sizeof(char));
	if (!str)
		return (NULL);
	merge_list_content(str, files);
	return (str);
}

/* _readdir() is a basic rountine that is used to bypass the 42 norm that
 * doesn't allow us to use variable assignment in a condition.
 * Doesn't malloc. */

static struct dirent	*_readdir(DIR *dir_stream, struct dirent **dir_ent)
{
	*dir_ent = readdir(dir_stream);
	return (*dir_ent);
}

static int	scan_current_directory(t_token *tkn)
{
	DIR				*dir_stream;
	struct dirent	*dir_ent;
	t_dlist			*files;

	errno = 0;
	files = NULL;
	dir_stream = opendir(CURRENT_DIR);
	if (!dir_stream)
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_OPENDIR, strerror(errno));
	while (_readdir(dir_stream, &dir_ent))
	{
		if (add_file_to_list(tkn, &files, dir_ent) == -1)
				break ;
	}
	if (dir_stream && errno != ENO)
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_READDIR, strerror(errno));
	else
		tkn->val = list_to_string(tkn, files);
	ft_dlstclear(&files, free);
	closedir(dir_stream);
	return (errno);
}

/* wildcard_expansion() returns a string if one or more files are matching the
 * pattern. If no files are found or an error occured, the function returns
 * NULL.
 * This string contains each filename separated by space by ascii order. */

t_token	*wildcard_expansion(t_token *tkn)
{
	scan_current_directory(tkn);
	return (tkn);
}
