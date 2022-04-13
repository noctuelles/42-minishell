/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:14:31 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/13 13:26:08 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

# include "env.h"

# define CD_FORMAT_ERROR "Minishell: %s: use with format: %s <relative or \
absolute path>\n"
# define EXIT_NUMERIC_REQUIRED "Minishell: %s: %s: numeric argument required\n"
# define EXIT_TO_MANY "Minishell: %s: too many arguments\n"
# define EXPORT_LIST "declare -x %s=\""
# define UNSET_NOT_ENOUGH "Minishell: %s: not enough arguments\n"

#endif