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

#include <stdio.h>
#include "minilibx-linux/mlx.h"
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	if (i == n)
		return (0);
	while ((i < ft_strlen(str1) && i < ft_strlen(str2)) && i < n)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}


int isvalid(char *str)
{
    int i;
    int has_decimal;
	int len;

	len = lenght(str);
	i = 0;
	has_decimal = 0;
	if (str[i] == '+' || str[i] == '-') 
		i++;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (has_decimal || i == 0 || i == len - 1)
                return 0;
			has_decimal = 1;
		} 
		else if (!ft_isdigit(str[i])) {
			return 0;
		}
		i++;
	}
	return (i > 0);
}
double ft_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    double result = 0.0;
    double decimal = 1.0;

    if (!str)
        return 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
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
			decimal /= 10;
			result += (str[i] - '0') * decimal;
			i++;
		}
	}
	return (result * sign);
}

int main(int ac, char **av)
{
	if (ac <= 4 && ac >= 2)
	{
		if (ft_strncmp(av[1], "mandelbrot", 10) == 0 )
			mandelbrot();
		else if (ft_strncmp(av[1], "julia", 5) == 0 && (ac ==4 ))
		{
			if (isvalid(av[2]) && isvalid(av[3]))
				julia(ft_atoi(av[2]), ft_atoi(av[3]));
			else
				printf("Error\n");
		}
		else
			printf("Error\n");
	}
	else
		printf("Error\n");
	return (0);	
}
