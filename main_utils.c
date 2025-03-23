/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:20:22 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/23 08:20:23 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	lenght(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int a)
{
	if ((a >= 48 && a <= 57))
	{
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *a)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	isvalid(char *str)
{
	int	i;
	int	has_decimal;
	int	len;

	len = lenght(str);
	i = 0;
	has_decimal = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			if (has_decimal || i == 0 || i == len - 1 || str[i - 1] == '-')
				return (0);
			has_decimal = 1;
		}
		else if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (i > 0);
}
