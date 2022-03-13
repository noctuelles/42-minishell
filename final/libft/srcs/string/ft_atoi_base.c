/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:22:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/26 12:51:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

/*
 *		ft_check_base: check the base follow these rules :
 *		If the base contains two times the same character
 *		If the base contains a + char or a - char or whitespaces.
 *		Return the base number.
 */

int	ft_check_base(char *str)
{
	int		i;
	int		j;
	char	actual_char;

	i = 0;
	while (str[i])
	{
		actual_char = str[i];
		if (actual_char == '+' || actual_char == '-' || ft_isspace(actual_char))
			return (0);
		j = i;
		while (str[++j])
			if (str[j] == actual_char)
				return (0);
		++i;
	}
	return (i);
}

/*
 *		ft_in_base: check if c belongs to base.
 *		Stores the value associated with c in base_rslt.
 *		Return -1 if c isn't in the base.
 */

int	ft_is_in_base(char *base, char c, int *base_rslt)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
		{
			*base_rslt = i;
			return (i);
		}
		++i;
	}
	return (-1);
}

/*
 *		ft_atoi_base: convert array to an integer value, according to the base.
 *		Return 0 if contains error:
 *		- base is size 1 or empty.
 *		- base contains two times the same character.
 *		- base contains + or - character.
 *		else return integer value.
 */

int	ft_atoi_base(char *str, char *base)
{
	int	base_nbr;
	int	sign;
	int	result;
	int	base_rslt;

	base_nbr = ft_check_base(base);
	sign = 1;
	result = 0;
	base_rslt = 0;
	if (base_nbr < 2)
		return (0);
	while (ft_isspace(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_is_in_base(base, *str++, &base_rslt) != -1)
		result = result * base_nbr + base_rslt;
	return (result * sign);
}
