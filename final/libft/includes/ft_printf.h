/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:32:08 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/24 01:10:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
					WELCOME TO THE
					   IF FOREST
					~~~~~~~~~~~~~~
		               ,@@@@@@@,
			   ,,,.   ,@@@@@@/@@,  .oo8888o.
			,&%%&%&&%,@@@@@/@@@@@@,8888\88/8o
		   ,%&\%&&%&&%,@@@\@@@/@@@88\88888/88'
		   %&&%&%&/%&&%@@\@@/ /@@@88888\88888'
		   %&&%/ %&%%&&@@\ V /@@' `88\8 `/88'
		   `&%\ ` /%&'    |.|        \ '|8'
			   |o|        | |         | |
			   |.|        | |         | |
		 \\/ ._\//_/__/  ,\_//__\\/.  \_//__/_

	 ____  ____      ____  ____  ____  _  _  ____  ____ 
	( ___)(_  _)    (  _ \(  _ \(_  _)( \( )(_  _)( ___)
	 )__)   )(  ___  )___/ )   / _)(_  )  (   )(   )__) 
	(__)   (__)(___)(__)  (_)\_)(____)(_)\_) (__) (__)  

	This printf has been carefully crafted with love, and to be maintened
	overtime. This is not the most optimized printf, but it's solid has a rock.
*/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>

# define STR_NULL "(null)"

# if defined (__APPLE__)
#  define PTR_NULL "0x0"
# elif __linux__
#  define PTR_NULL "(nil)"
# endif

# define FLAGS "-0# +"
# define CONVERSION "cspdiuxX%"
# define HEX_LOWERCASE "0123456789abcdef"
# define HEX_UPPERCASE "0123456789ABCDEF"
# define DECIMAL "0123456789"

enum e_printf_flags
{
	NO_FLAGS=0x00,
	L_JUST=0x01,
	R_JUST=0x02,
	SIGN=0x04,
	AF=0x08,
	SPACE=0x10,
	ZERO_PAD=0x20,
	PRCS=0x40,
	NEG=0x80,
	ZERO_VAL=0x100,
	NULL_STR=0x200,
	PERCENT=0x400
};

typedef struct s_printf_buffers
{
	char	*right;
	char	*main;
	char	*left;
	size_t	m_len;
}				t_printf_buffers;

typedef struct s_printf_info
{
	t_printf_buffers	bufs;
	char				conv;
	size_t				wlen;
	size_t				prcs_add;
	size_t				pad_add;
	uint16_t			flags : 11;
	size_t				width;
	size_t				precision;
}				t_printf_info;

/* printf_parsing.c */

const char	*printf_parse(const char *flags, va_list ap, t_printf_info *info);

/* ft_printf.c */

int			printf_conversion(char spec, va_list ap, t_printf_info *info);
int			ft_printf(const char *format, ...);

/* printf_utils.c */

void		printf_flush_info(t_printf_info *info);
void		printf_update_mlen(t_printf_info *info);
t_bool		printf_is_valid_flag(char c);
t_bool		printf_is_nbr_conv(t_printf_info *info);

/* printf_apply.c */

void		printf_flags_compute_n_apply(t_printf_info *info);

/* printf_compute.c */

void		printf_compute_precision_add(t_printf_info *info);
void		printf_compute_padding_len(t_printf_info *info);

/* printf_puts.c */

void		printf_put_buffers(t_printf_info *info);
void		printf_putchar(char c, t_printf_info *info);
void		printf_putstr(const char *str, t_printf_info *info);
void		print_infos(t_printf_info info);

/* printf_conversion.c */

int			printf_conversion(char spec, va_list ap, t_printf_info *info);

/* printf_ansi.c */

const char	*printf_putansi(const char *ansi, t_printf_info *info);

#endif
