/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:19:21 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/21 16:33:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "ft_dprintf.h"

char	*get_lexer_error(t_lexer_errcode errcode)
{
	if (errcode == ERR_PRT)
		return (STR_INVALID_PRT);
	else if (errcode == ERR_QUOTE)
		return (STR_INVALID_QUOTE);
	return (STR_LEXICAL_ERR);
}

char	*get_parser_error(t_parser_errcode errcode)
{
	if (errcode == ERR_UNEXPECTED_IO_TOKEN)
		return (STR_ERR_UNEXPECTED_IO_TOKEN);
	else if (errcode == ERR_UNEXPECTED_IO_HEREDOC_TOKEN)
		return (STR_ERR_UNEXPECTED_IO_HEREDOC_TOKEN);
	else if (errcode == ERR_UNEXPECTED_TOKEN)
		return (STR_ERR_UNEXPECTED_TOKEN);
	else if (errcode == ERR_EXPECTED_COMMAND)
		return (STR_ERR_EXPECTED_COMMAND);
	else if (errcode == ERR_INVALID_PRT)
		return (STR_INVALID_PRT);
	else if (errcode == ERR_MALLOC)
		return (STR_MALLOC);
	else
		return (STR_SYNTAX_ERROR);
}

void	*display_error(void)
{
	ft_dprintf(STDERR_FILENO, STR_ERROR, strerror(errno));
	return (NULL);
}

void	*display_error_more(t_minishell *minishell, const char *fcnt_name,
		int err)
{
	if (minishell)
		minishell->err = err;
	ft_dprintf(STDERR_FILENO, STR_ERROR_M, fcnt_name, strerror(errno));
	return (NULL);
}
