/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:23:21 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/23 10:23:23 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define HEIGHT 1920
#define WIDTH 1080

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	rgb(int i)
{
	int	r;
	int	g;
	int	b;

	r = (i * 19) % 256;
	g = (i * 10) % 256;
	b = (i * 8) % 256;
	return (r * 65536 + g * 256 + b);
}

int	i_equalt_to(double zx, double zy, int i_max, t_data *shap)
{
	int (i);
	double (zr), (zi);
	i = 0;
	while (zx * zx + zy * zy < 4 && i < i_max)
	{
		zr = (zx * zx) - (zy * zy) + shap->gr->cx;
		zi = 2 * zx * zy + shap->gr->cy;
		zx = zr;
		zy = zi;
		i++;
	}
	return (i);
}

void	init_man(t_data *shape)
{
	shape->mlx = mlx_init();
	if (!shape->mlx)
	{
		ft_printf("MLX FAIL");
		exit(1);
	}
	shape->mlx_win = mlx_new_window(shape->mlx, 1920, 1080, "MANDELBROT");
	if (!shape->mlx_win)
	{
		ft_printf("MLX FAIL");
		close_mandl(shape);
	}
	shape->img = mlx_new_image(shape->mlx, 1920, 1080);
	if (!shape->img)
	{
		ft_printf("MLX FAIL");
		close_mandl(shape);
	}
	shape->addr = mlx_get_data_addr(shape->img, &shape->bits_per_pixel,
			&shape->line_length, &shape->endian);
	if (!shape->addr)
	{
		ft_printf("MLX FAIL");
		close_mandl(shape);
	}
}
