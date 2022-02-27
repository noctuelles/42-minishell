/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:57:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/27 18:44:24 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	ft_env(int argc, char **argv, t_env **env);
int	ft_unset(int argc, char **argv, t_env **env);
int	ft_pwd(int argc, char **argv, t_env **env);
int	ft_export(int argc, char **argv, t_env **env);
int	ft_echo(int argc, char **argv, t_env **env);
int	ft_cd(int argc, char **argv, t_env **env);

int main(int argc, char **argv, char **envp)
{
	t_env *env = get_env_list(envp);

	/* ENV test
	char **args = malloc(sizeof(char*) * 1);
	args[0] = strdup("env");
	ft_env(1, args, &env);
	*/

	/* UNSET test
	if(is_var_with_name(&env, "PWD"))
		printf("%s\n", get_value(&env, "PWD"));
	else
		printf("Not seted var\n");
	char **args = malloc(sizeof(char*) * 2);
	args[0] = strdup("unset");
	args[1] = strdup("PWD");
	ft_unset(2, args, &env);
	if(is_var_with_name(&env, "PWD"))
		printf("%s\n", get_value(&env, "PWD"));
	else
		printf("Not seted var\n");
	*/

	/* PWD test 
	char **args = malloc(sizeof(char*) * 1);
	args[0] = strdup("pwd");
	ft_pwd(1, args, &env);
	*/

	/* Export test
	if(is_var_with_name(&env, "TEST"))
		printf("%s\n", get_value(&env, "TEST"));
	else
		printf("Not seted var\n");
	if(is_var_with_name(&env, "TEST2"))
		printf("%s\n", get_value(&env, "TEST2"));
	else
		printf("Not seted var\n");
	char **args = malloc(sizeof(char*) * 3);
	args[0] = strdup("export");
	args[1] = strdup("TEST=test");
	args[2] = strdup("TEST2");
	ft_export(3, args, &env);
	printf("-------\n");
	if(is_var_with_name(&env, "TEST"))
		printf("%s\n", get_value(&env, "TEST"));
	else
		printf("Not seted var\n");
	if(is_var_with_name(&env, "TEST2"))
		printf("%s\n", get_value(&env, "TEST2"));
	else
		printf("Not seted var\n");
	*/

	/* ECHO test
	char **args = malloc(sizeof(char*) * 5);
	args[0] = strdup("echo");
	args[1] = strdup("-n");
	args[2] = strdup("comment");
	args[3] = strdup("ca");
	args[4] = strdup("va");
	ft_echo(5, args, &env);
	*/

	/* CD test
	printf("%s\n", get_value(&env, "PWD"));
	char **args = malloc(sizeof(char*) * 2);
	args[0] = strdup("../test");
	args[1] = strdup("awdwas");
	ft_cd(2, args, &env);
	printf("%s\n", get_value(&env, "PWD"));
	*/
}