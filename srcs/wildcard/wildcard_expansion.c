/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:50:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/05 15:57:43 by plouvel          ###   ########.fr       */
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
static t_dlist	*scan_current_directory(t_token *tkn) { DIR				*dir_stream;
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

/* check_if_expandable() checks if the current token can be expanded.
 * If the user is using the export builtin, in the variable assignation,
 * no wildcard shall be expanded. */

static bool	check_if_expandable(t_dlist *elem)
{
	t_token	*tkn;

	while (elem->prev != NULL)
	{
		elem = elem->prev;
		tkn = elem->content;
		if (tkn->type == T_PIPE || tkn->type == T_LOG_AND
				|| tkn->type == T_LOG_OR)
		{
			tkn = elem->next->content;
			break ;
		}
	}
	while (tkn->type == T_OP_PRT)
	{
		elem = elem->next;
		tkn = elem->content;
	}
	if (ft_strcmp(tkn->val, STR_BUILTIN_EXPORT) == 0)
		return (false);
	return (true);
}

/* wildcard_expansion() returns a string if one or more files are matching the
 * pattern. If no files are found or an error occured, the function returns
 * NULL.
 * This string contains each filename separated by space by ascii order. */

t_dlist	*wildcard_expansion(t_dlist **tkns, t_dlist *elem, t_token *tkn)
{
	t_dlist	*files;

	if (ft_strchr(tkn->val, '=') != NULL && check_if_expandable(elem) == false)
	{
		printf("token %s is not expanded.\n", tkn->val);
		return (elem);
	}
	files = scan_current_directory(tkn);
	return (insert_list(tkns, files, elem));
}
