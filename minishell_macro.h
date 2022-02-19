/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macro.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:33:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/19 23:33:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_MACRO_H
# define MINISHELL_MACRO_H

# define STR_HELP "\
42 Minishell project, written by dhubleur and plouvel.\n\n\
\
List of supported builtin:\n\n\
\
 echo [-n] [arg ...] : display string.\n\
 cd [dir]            : change current working directory.\n\
 pwd                 : print working directory.\n\
 export [var]        : export variable to child process.\n\
 unset [var]         : wipe specified variable.\n\
 env                 : print environnement variables.\n\
 exit                : exit the shell.\n\n"

# define STR_CMD_NFND    "command not found."
# define ERRNO_CMD_NFND  127

# define STR_PARSE_ERR   "parse error."
# define ERRNO_PARSE_ERR 1

#endif
