/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:07:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/19 23:34:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/* T_LITTERAL : a litteral is string not recognize as any other token .
 * T_BUILTIN  : recognize as a buildin command.
 * T_CRTL_OP  : recognize as a control operator. || && '(' ')'.
 * T_RDCT_OP  : recognize as a redirection operator. < << > >>.
 * T_FILENAME : recognize as a filename.*/

/* value    : original value of the token.
 * expanded : expanded value of the token.*/ 

typedef struct s_token
{
	char	*value;
	char	*expanded;
} t_token;

typedef enum e_tokentype
{
	T_LITTERAL,
	T_BUILTIN,
	T_CRTL_OP,
	T_RDCT_OP,
	T_PROGRAM,
	T_VARIABLE
} t_tokentype;

typedef struct s_minishell
{
	t_list	*env;
} t_minishell;

#endif
