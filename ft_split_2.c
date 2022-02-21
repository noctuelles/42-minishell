/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:05:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/20 20:02:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

bool	is_a_quote(char c, char quote)
{
	if (quote == '\0')
	{
		if (c == '\"' || c == '\'')
			return (true);
		else
			return (false);
	}
	else
	{
		if (c == '\"' && quote == c)
			return (true);
		else if (c == '\'' && quote == c)
			return (true);
		else
			return (false);
	}
}

bool	is_a_metachar(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		i++;
	}
	return (false);
}
/* "ceci     est un (test).*/

size_t	get_nbr_token(char *str, char *charset)
{
	size_t	tokens;
	bool	in_word;
	char	quote;

	tokens = 0;
	in_word = false;
	quote = '\0';
	while (*str != '\0')
	{
		if (!quote)
		{
			if (is_a_metachar(*str, charset))
			{
				if (is_a_quote(*str, quote))
					quote = *str;
				do_break_word(&in_word, &tokens);
				tokens++;
			}
			else if (*str == ' ')
				do_break_word(&in_word, &tokens);
			else if (!in_word)
				in_word = true;
		}
		else
		{
			if (is_a_quote(*str, quote))
			{
				tokens++;
				if (!is_a_quote(*(str - 1), quote))
					tokens++;
				quote = '\0';
			}
		}
		str++;
	}
	if (in_word || (quote && !is_a_quote(*(str - 1), quote)))
		tokens++;
	return (tokens);
}

size_t	get_token_len(char *str, char *charset, char *quote)
{
	size_t	i;

	i = 0;
/*	if (is_a_metachar(str[i], charset))
	{
		if (is_a_quote(str[i], *quote) && *quote == '\0')
			*quote = str[i];
		else
			*quote = '\0';
		return (1);
	}*/
	if (*quote)
	{
		while (str[i] != '\0' && str[i] != *quote)
			i++;
		if (str[i] == *quote)
		{
			puts("end quote");
			*quote = '\0';
		}
	}
	else
	{
		if (is_a_metachar(str[i], charset))
		{
			printf("found meta char : %c\n", str[i]);
			if (is_a_quote(str[i], *quote))
				*quote = str[i];
			return (1);
		}
		while (str[i] != '\0' && !is_a_metachar(str[i], charset) && str[i] != ' ')
			i++;
	}
	return (i);
}

void	jmp_to_token(char **str, char *charset, char quote)
{
	size_t	i;

	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] == ' ' && !quote)
		i++;
	*str = &(*str)[i];
}

char	**ft_tokenize_str(char *str, char *charset)
{
	char	**tokens;
	size_t	nbr_token;
	size_t	token_len;
	char	quote = '\0';
	size_t	i;
	size_t	j;

	nbr_token = get_nbr_token(str, charset);
	tokens = (char **) malloc((nbr_token + 1) * sizeof(char *));
	printf("nbr of tokens : %zu\n", nbr_token);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < nbr_token)
	{
		j = 0;
		jmp_to_token(&str, charset, quote);
		token_len = get_token_len(str, charset, &quote);
		tokens[i] = (char *) malloc((token_len + 1) * sizeof(char));
		if (!tokens[i])
			return (NULL);
		while (j < token_len)
			tokens[i][j++] = *str++;
		tokens[i][j] = '\0';
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(int argc, char **argv)
{
	/*size_t	nbr_token = get_nbr_token(argv[1], argv[2]);
	printf("nbr token %zu\n", nbr_token);*/
	char	**tokens = ft_tokenize_str(argv[1], argv[2]);
	for (int i = 0; tokens[i]; i++)
		puts(tokens[i]);
}
