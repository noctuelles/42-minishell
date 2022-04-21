/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:39:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/21 16:07:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

/******************************************************************************
 *                                  Macros                                    *
 *****************************************************************************/

# define STR_PIPE             "|"
# define STR_LOG_OR           "||"
# define STR_LOG_AND          "&&"
# define STR_RD_FILE          ">"
# define STR_RD_STDIN         "<"
# define STR_RD_FILE_APN      ">>"
# define STR_RD_STDIN_HEREDOC "<<"
# define STR_OP_PRT           "("
# define STR_CL_PRT           ")"
# define STR_SP               " "
# define STR_TAB              "\t"

# define STR_INVALID_PRT     "invalid parenthesis use"
# define STR_INVALID_QUOTE   "quote not closed"
# define STR_LEXICAL_ERR     "lexical error"

# define SQUOTE               '\''
# define DQUOTE               '"'

/******************************************************************************
 *                              Typedef & Enum                                *
 *****************************************************************************/

typedef enum e_token_type
{
	T_PIPE,
	T_LOG_AND,
	T_LOG_OR,
	T_LESS,
	T_DLESS,
	T_GRT,
	T_DGRT,
	T_OP_PRT,
	T_CL_PRT,
	T_WORD,
	T_EQUALS,
	T_BREAK,
	T_NULL
}			t_token_type;

typedef enum e_errcode
{
	ERR_NO,
	ERR_MEM,
	ERR_QUOTE,
	ERR_PRT
}				t_lexer_errcode;

typedef struct s_token
{
	char			*val;
	size_t			len;
	t_token_type	type;
}				t_token;

typedef struct s_lexer
{
	t_dlist			*tkns;
	unsigned int	prt_cnt;
	char			*str;
	char			*prev;
	t_token			tkn;
	bool			bbreak;
}				t_lexer;

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

/* lexer.c */

t_dlist	*lex_str(const char *str);

/* lexer_mem_utils.c */

t_token	*new_token(char *val, size_t len, t_token_type type);
void	free_token(void *tkn);

/* lexer_utils.c */

t_token	*add_to_tkns(t_dlist **tkns, char *val, size_t len,
			t_token_type type);
t_token	set_token(t_token *tkn, char *val, size_t len,
			t_token_type type);
t_token	search_existing_token(const char *str);

#endif
