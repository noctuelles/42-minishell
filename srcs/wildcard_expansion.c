/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:50:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/30 17:11:58 by plouvel          ###   ########.fr       */
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

/* _readdir() is a basic rountine that is used to bypass the 42 norm that
 * doesn't allow us to use variable assignment in a condition.
 * Doesn't malloc. */

static struct dirent	*_readdir(DIR *dir_stream, struct dirent **dir_ent)
{
	*dir_ent = readdir(dir_stream);
	return (*dir_ent);
}

static t_dlist	*scan_current_directory(t_token *tkn)
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
	{
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_READDIR, strerror(errno));
		ft_dlstclear(&files, free_token);
	}
	closedir(dir_stream);
	return (files);
}

t_dlist	*link_files_to_tkn_list(t_lexer *lexer, t_dlist *elem, t_dlist *files)
{
	t_dlist	*files_last;

	if (!files)
		return (elem);
	files_last = ft_dlstlast(files);
	if (elem->prev)
	{
		elem->prev->next = files;
		files->prev = elem->prev;
	}
	else
		lexer->tkns = files;
	if (elem->next)
	{
		elem->next->prev = files_last;
		files_last->next = elem->next;
	}
	free_token(elem->content);
	free(elem);
	return (files_last);
}

/* wildcard_expansion() returns a string if one or more files are matching the
 * pattern. If no files are found or an error occured, the function returns
 * NULL.
 * This string contains each filename separated by space by ascii order. */

t_dlist	*wildcard_expansion(t_lexer *lexer, t_dlist *elem, t_token *tkn)
{
	t_dlist	*files;

	files = scan_current_directory(tkn);
	return (link_files_to_tkn_list(lexer, elem, files));
}
