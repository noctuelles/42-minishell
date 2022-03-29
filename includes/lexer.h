/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:39:17 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/28 18:39:26 by plouvel          ###   ########.fr       */
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
# define STR_SP               " "

# define STR_INVALID_PRT     "invalid parenthesis use"
# define STR_INVALID_QUOTE   "quote not closed"
# define STR_LEXICAL_ERR     "lexical error"

# define SQUOTE               '\''
# define DQUOTE               '"'

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
	t_list			*wldc_list;
	t_list			*quote_list;
	t_token_type	type;
	int test;
}				t_token;

typedef struct s_lexer
{
	t_token			*tkns;
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
void	free_lexer(t_lexer *lexer);
t_token	search_existing_token(const char *str);

/* lexer_post_process.c */

void	remove_quote_from_tkns(t_lexer *lexer);
void	expand_var_from_tkns(t_dlist *lst_var, t_lexer *lexer);

/* lexer.c */

int	fill_lexer_from_str(t_lexer *lexer, char *str);

/* lexer_post_process.c */

void	expand_var_from_tkns(t_dlist *lst_var, t_lexer *lexer);

/* lexer_var_expansion.c */

char	*expand_tkn(t_dlist *lst_var, char *str);

#endif
