/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:00:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 15:18:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /!\ compile with -lreadline

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	ft_strlen(char *str)
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

int main()
{
	char *line;
	char *prompt;

	char *USER = "dhubleur";
	char *HOSTNAME = "e2r4p6";
	char *PWD = "~/Document/42-minishell";

	while(1)
	{
		prompt = malloc(sizeof(char) * (ft_strlen(USER) + ft_strlen(HOSTNAME) + ft_strlen(PWD) + 7));
		prompt[0] = '\0';
		strcat(prompt, USER);
		strcat(prompt, "@");
		strcat(prompt, HOSTNAME);
		strcat(prompt, ":");
		strcat(prompt, PWD);
		strcat(prompt, " > ");

		line = readline(prompt);
		free(prompt);
		if(line == NULL)
			break;
		add_history(line);
		printf("%s\n", line);
	}
	printf("\nExit\n");
}