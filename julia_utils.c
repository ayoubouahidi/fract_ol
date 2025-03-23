/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:59:01 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/23 10:59:04 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put_julia(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgb_julia(int i)
{
	int	r;
	int	g;
	int	b;

	r = (i * 5) % 256;
	g = (i * 50) % 256;
	b = (i * 80) % 256;
	return (r * 65536 + g * 256 + b);
}

int	i_equalt_to_j(double zx, double zy, int i_max, t_data *shap)
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

void	draw_julia(t_data *shap)
{
	double (x), (y), (zx), (zy);
	int (i), (i_max);
	y = 0;
	i_max = 100.0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			zx = shap->gr->x_min + x / HEIGHT
				* (shap->gr->x_max - shap->gr->x_min);
			zy = shap->gr->y_min + y / WIDTH
				* (shap->gr->y_max - shap->gr->y_min);
			i = i_equalt_to_j(zx, zy, i_max, shap);
			if (i == i_max)
				my_mlx_pixel_put_julia(shap, x, y, 0x000000);
			else
				my_mlx_pixel_put_julia(shap, x, y, rgb_julia(i));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(shap->mlx, shap->mlx_win, shap->img, 0, 0);
}

int	mouse_hook_julia( int button, int x, int y, void *param)
{
	t_data	*shape;

	(void)x;
	(void)y;
	shape = (t_data *)param;
	if (!shape)
		return (0);
	if (button == 5)
	{
		shape->gr->x_max = shape->gr->x_max * 1.2;
		shape->gr->x_min *= 1.2;
		shape->gr->y_max *= 1.2;
		shape->gr->y_min *= 1.2;
	}
	else if (button == 4)
	{
		shape->gr->x_max = shape->gr->x_max / 1.2;
		shape->gr->x_min /= 1.2;
		shape->gr->y_max /= 1.2;
		shape->gr->y_min /= 1.2;
	}
	draw_julia(shape);
	mlx_put_image_to_window(shape->mlx, shape->mlx_win, shape->img, 0, 0);
	return (0);
}
