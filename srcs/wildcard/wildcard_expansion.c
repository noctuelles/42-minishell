/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:50:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/16 01:47:26 by plouvel          ###   ########.fr       */
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
		return (-1);
	while (_readdir(dir_stream, &dir_ent))
	{
		if (add_file_to_list(arg, files, dir_ent) == -1)
			break ;
	}
	closedir(dir_stream);
	if (errno != ENO)
	{
		ft_dlstclear(files, free_token);
		if (!dir_ent)
			return (-2);
		else
			return (-3);
	}
	return (0);
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

static void	*print_errmsg (int errcode)
{
	if (errcode == -1)
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_OPENDIR, strerror(errno));
	else if (errcode == -2)
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_READDIR, strerror(errno));
	else if (errcode == -3)
		ft_dprintf(STDERR_FILENO, STR_ERROR_M, STR_MALLOC, strerror(errno));
	return (NULL);
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
	int		errcode;

	files = NULL;
	if (ft_strchr(arg->value, '*') == NULL)
		return (elem);
	if (ft_strchr(arg->value, '=') != NULL && check_if_expandable(elem) == false)
		return (elem);
	errcode = scan_current_directory(&files, arg);
	if (errcode != 0)
		return (print_errmsg(errcode));
	ft_lstclear(&arg->wldc_lst, NULL);
	return (insert_list(args, files, elem));
}
