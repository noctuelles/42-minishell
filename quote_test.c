/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:27:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/02/18 15:35:32 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int is_expression_correctly_quoted(char *str)
{
	int in_simple;
	int in_double;
	int	i;

	in_simple = 0;
	in_double = 0;
	i =-1;
	while (str[++i])
	{
		if(str[i] != '\'' && str[i] != '\"')
			continue;
		if((in_simple && str[i] == '\"') || (in_double && str[i] == '\''))
			continue;
		if(str[i] == '\'')
		{
			if(in_simple)
				in_simple = 0;
			else
				in_simple = 1;
		}
		if(str[i] == '\"')
		{
			if(in_double)
				in_double = 0;
			else
				in_double = 1;
		}
	}
	if(in_simple)
		return -1;
	if(in_double)
		return -2;
	return 1;
}