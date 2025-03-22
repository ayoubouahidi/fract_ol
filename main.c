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
static long	fornotminette1(long result, int cmpt, int cmpmoins, int *err)
{
	if (cmpt > 1)
		return (0);
	if (cmpmoins == 1)
		result = result * -1;
	(void)err;
	return (result);
}

long	ft_atoi_err(const char *str, int *err)
{
	int		i;
	int		cmpt;
	long	result;
	int		cmpmoins;

	cmpmoins = 0;
	result = 0;
	cmpt = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32 && str[i] != '\0'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		cmpt++;
		cmpmoins += (str[i] == '-');
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i++] - 48);
		if (((result > 2147483647) && !cmpmoins)
			|| ((result > 2147483648) && cmpmoins))
			*err = 1;
	}
	return (fornotminette1(result, cmpt, cmpmoins, err));
}
char	*isvalid(char *av)
{
	int		i;
	long	result;
	int		err;

	i = 0;
	if (av[0] != '-' && av[0] != '+' && !ft_isdigit(av[0]))
		return (NULL);
	if ((av[0] == '-' || av[0] == '+') && lenght(av) == 1)
		return (NULL);
	i++;
	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]) )
			return (NULL);
		i++;
	}
	err = 0;
	result = ft_atoi_err(av, &err);
	(void)result;
	if (err)
		return (NULL);
	return ("is valid ");
}

int main(int ac, char **av)
{
	if (ac <= 4 && ac >= 2)
	{
		if (ft_strncmp(av[1], "mandelbrot", 10) == 0 )
		mandelbrot();
		else if (ft_strncmp(av[1], "julia", 5) == 0 && (ac <=4 && ac >= 2))
		{
			if ((av[2][0] == '\0' || !is_valid_arg(av[2])) && (av[3][0] == '\0' || !is_valid_arg(av[3])))
				julia();

		}
		else
			printf("Error\n");
	}
	else
		printf("Error\n");
	return (0);	
}
