/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:19:21 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/18 19:34:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (errcode == ERR_UNEXPECTED_EOF)
		return (STR_ERR_UNEXPECTED_EOF);
	else if (errcode == ERR_EXPECTED_COMMAND)
		return (STR_ERR_EXPECTED_COMMAND);
	else
		return (STR_SYNTAX_ERROR);
}