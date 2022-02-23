/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:39:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/23 11:40:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define STR_PIPE             "|"
# define STR_LOG_OR           "||"
# define STR_LOG_AND          "&&"
# define STR_RD_FILE          ">"
# define STR_RD_STDIN         "<"
# define STR_RD_FILE_APN      ">>"
# define STR_RD_STDIN_HEREDOC "<<"
# define STR_OP_PRT           "("
# define STR_CL_PRT           ")"
# define STR_EQUALS           "="
# define STR_SP               " "

# define SQUOTE               '\''
# define DQUOTE               '"'

typedef enum e_token_type
{
	T_PIPE,
	T_LOG_AND,
	T_LOG_OR,
	T_REDIR,
	T_OP_PRT,
	T_CL_PRT,
	T_STRING,
	T_EQUALS,
	T_BREAK,
	T_NULL
}			t_token_type;

typedef enum e_errcode
{
	E_MEM,
	E_QUOTE,
	E_PRT
}				t_errcode;

typedef struct s_token
{
	char			*val;
	size_t			len;
	t_token_type	type;
}				t_token;

typedef struct s_lexer
{
	t_token			*tkns;
	int				errcode;
	size_t			size;
	size_t			idx;
	unsigned int	prt_cnt;
	char			*prev;
}				t_lexer;

/* lexer_memutils.c */

void	free_tkns(t_token *tkns, size_t size);
t_token	*grow_tkns_array(t_lexer *lexer);

/* lexer_utils.c */

t_token	set_token(t_token *tkn, char *val, size_t len,
			t_token_type type);
t_token	search_existing_token(const char *str);
void	*set_lexer_errcode(t_lexer *lexer, int errcode);

/* lexer.c */

t_lexer	*fill_lexer_from_str(t_lexer *lexer, char *str);

#endif
