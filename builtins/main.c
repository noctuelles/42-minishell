/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:57:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 14:21:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_env(int argc, char **argv, t_env **env);
int	ft_unset(int argc, char **argv, t_env **env);
int	ft_pwd(int argc, char **argv, t_env **env);

int main(int argc, char **argv, char **envp)
{
	t_env *env = get_env_list(envp);

	/* ENV test
	char **args = malloc(sizeof(char*) * 2);
	args[0] = strdup("env");
	args[1] = NULL;
	ft_env(1, args, &env);
	*/

	/* UNSET test
	if(is_var_with_name(&env, "PWD"))
		printf("%s\n", get_value(&env, "PWD"));
	else
		printf("Not seted var\n");
	char **args = malloc(sizeof(char*) * 3);
	args[0] = strdup("unset");
	args[1] = strdup("PWD");
	args[2] = NULL;
	ft_unset(2, args, &env);
	if(is_var_with_name(&env, "PWD"))
		printf("%s\n", get_value(&env, "PWD"));
	else
		printf("Not seted var\n");
	*/

	/* PWD test 
	char **args = malloc(sizeof(char*) * 2);
	args[0] = strdup("pwd");
	args[1] = NULL;
	ft_pwd(1, args, &env);
	*/
}