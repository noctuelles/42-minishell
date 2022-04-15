/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:50:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/15 12:16:15 by plouvel          ###   ########.fr       */
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

/* scan_current_directory() scan each files into the current working directory,
 * and add it to the list files if a file match the pattern (the pattern is the
 * value of the tkn).
 * If an error occurs, it returns the value of errno, and not NULL because files
 * can be NULL even if no error occurs.*/

static int	scan_current_directory(t_dlist **files, t_arg *arg)
{
	DIR				*dir_stream;
	struct dirent	*dir_ent;

	errno = 0;
	dir_stream = opendir(CURRENT_DIR);
	if (!dir_stream)
		return (errno);
	while (_readdir(dir_stream, &dir_ent))
	{
		if (add_file_to_list(arg, files, dir_ent) == -1)
			break ;
	}
	if (errno != ENO)
		ft_dlstclear(files, free_token);
	closedir(dir_stream);
	return (errno);
}

/* check_if_expandable() checks if the current token can be expanded.
 * If the user is using the export builtin, in the variable assignation,
 * no wildcard shall be expanded. */

static bool	check_if_expandable(t_dlist *elem)
{
	t_token	*tkn;

	if (elem->prev != NULL)
	{
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
	}
	return (true);
}

/* wildcard_expansion() returns a pointer to the next element.
 * If one or more files in the working directory match the pattern (the pattern
 * is the token value), the current element in the list get replaced by a 
 * sub-list called files.
 * If no match are found, the function returns NULL.
 * If an allocation error or an I/O error is found, the function returns NULL.
 * Because both cases returns NULL, must check errno. */

t_dlist	*wildcard_expansion(t_dlist **args, t_dlist *elem, t_arg *arg)
{
	t_dlist	*files;

	files = NULL;
	if (ft_strchr(arg->value, '=') != NULL && check_if_expandable(elem) == false)
		return (elem);
	if (scan_current_directory(&files, arg) != 0)
		return (NULL);
	ft_lstclear(&arg->wldc_lst, NULL);
	return (insert_list(args, files, elem));
}
