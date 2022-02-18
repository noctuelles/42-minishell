/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:00:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 16:25:40 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /!\ compile with -lreadline

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void print_syntax_error(int res)
{
	char error;

	if(res == -1)
		printf("Syntax error: \' never closed\n");
	if(res == -2)
		printf("Syntax error: \" never closed\n");
}

int is_expression_correctly_quoted(char *str);
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env *get_env_list(char **envp);
char *get_value(t_env **env_list, char *name);

int main(int argc, char **argv, char **envp)
{
	char *line;
	char *prompt;

	char *USER;
	char *PWD;

	t_env *env = get_env_list(envp);
	if(!env)
		return 1;
	
	while(1)
	{
		USER = get_value(&env, "USER");
		if(!USER)
		{
			printf("USER variable not found\n");
			return 1;
		}
		PWD = get_value(&env, "PWD");
		if(!PWD)
		{
			printf("PWD variable not found\n");
			return 1;
		}

		prompt = malloc(sizeof(char) * (ft_strlen(USER) + ft_strlen(PWD) + 6));
		prompt[0] = '\0';
		strcat(prompt, USER);
		strcat(prompt, "@");
		strcat(prompt, PWD);
		strcat(prompt, " > ");

		line = readline(prompt);
		free(prompt);
		if(line == NULL)
			break;
		add_history(line);
		
		int res = is_expression_correctly_quoted(line);
		if(res == 1)
			printf("Execute: %s\n", line);
		else
			print_syntax_error(res);
	}
	printf("\nExit\n");
}