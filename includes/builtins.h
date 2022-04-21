/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:14:31 by dhubleur          #+#    #+#             */
/*   Updated: 2022/04/21 16:24:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "env.h"

/******************************************************************************
 *                                  Macros                                    *
 *****************************************************************************/

# define CD_FORMAT_ERROR       "minishell: %s: use with format: %s <relative> \
or absolute path>\n"
# define EXIT_NUMERIC_REQUIRED "minishell: %s: %s: numeric argument required\n"
# define EXIT_TO_MANY          "minishell: %s: too many arguments\n"
# define EXPORT_LIST           "declare -x %s=\""
# define UNSET_NOT_ENOUGH      "minishell: %s: not enough arguments\n"
# define ERROR_ERRNO           "minishell: %s: %s\n"

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

int		ft_cd(int argc, char **argv, t_minishell *minishell);
int		ft_echo(int argc, char **argv, t_minishell *minishell);
int		ft_env(int argc, char **argv, t_minishell *minishell);
int		ft_export(int argc, char **argv, t_minishell *minishell);
int		ft_pwd(int argc, char **argv, t_minishell *minishell);
int		ft_unset(int argc, char **argv, t_minishell *minishell);
int		ft_exit(int argc, char **argv, t_minishell *minishell);
void	clean_everything(t_minishell *minishell);

#endif
