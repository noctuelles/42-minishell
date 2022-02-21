/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:17:18 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/20 19:23:35 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdbool.h>

void	do_break_word(bool *in_word, size_t *tokens)
{
	if (*in_word)
	{
		(*tokens)++;
		*in_word = false;
	}
}
