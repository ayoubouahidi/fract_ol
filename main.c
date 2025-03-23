/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:25:47 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/21 18:25:49 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

double	check_calcul(char *str, int i)
{
	double	dicimal;
	double	result;

	result = 0;
	dicimal = 1.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			dicimal /= 10;
			result += (str[i] - '0') * dicimal;
			i++;
		}
	}
	return (result);
}

double	ft_atoi(char *str)
{
	int		i;
	int		sign;
	double	res;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = check_calcul(str, i);
	return (res * sign);
}

int	main(int ac, char **av)
{
	if (ac <= 4 && ac >= 2)
	{
		if (ft_strcmp(av[1], "mandelbrot") == 0)
			mandelbrot();
		else if (ft_strcmp(av[1], "julia") == 0 && (ac == 4))
		{
			if (isvalid(av[2]) && isvalid(av[3]))
				julia(ft_atoi(av[2]), ft_atoi(av[3]));
			else
				ft_printf("Error\n");
		}
		else
			ft_printf("Error\n");
	}
	else
		ft_printf("Error\n");
	return (0);
}
