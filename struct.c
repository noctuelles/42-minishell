/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:35:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/19 20:48:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_tokentype
{
	T_LITTERAL = 0b0000000,
	T_BUILTIN  = 0b00000001,
	T_CRTL_OP  = 0b00000010,
	T_FILENAME = 0b00000100,
	T_PROGRAM  = 0b00001000,
	T_VARIABLE = 0b00010000
} t_tokentype;

typedef struct	s_token
{
	char		*value;
	t_tokentype	type;
}
