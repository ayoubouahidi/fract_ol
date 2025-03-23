/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:41:52 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/19 23:41:54 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "fractol.h"
#define HEIGHT 1920
#define WIDTH 1080

void	drawing_mandelbort(t_data *shap)
{
	double (x), (y), (zx), (zy);
	int (i), (i_max);
	y = 0;
	i_max = 100.0;
	while (y < WIDTH)
	{
		shap->gr->cy = shap->gr->y_min + y / WIDTH
			* (shap->gr->y_max - shap->gr->y_min);
		x = 0;
		while (x < HEIGHT)
		{
			shap->gr->cx = shap->gr->x_min + x / HEIGHT
				* (shap->gr->x_max - shap->gr->x_min);
			zx = 0.0;
			zy = 0.0;
			i = i_equalt_to(zx, zy, i_max, shap);
			if (i == i_max)
				my_mlx_pixel_put(shap, x, y, 0x000000);
			else
				my_mlx_pixel_put(shap, x, y, rgb(i));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(shap->mlx, shap->mlx_win, shap->img, 0, 0);
}

int	close_mandl(t_data *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->mlx_win)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

int	escape_mand(int keycode, t_data *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 65307)
		close_mandl(vars);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*shape;

	shape = (t_data *)param;
	(void)x;
	(void)y;
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
	drawing_mandelbort(shape);
	mlx_put_image_to_window(shape->mlx, shape->mlx_win, shape->img, 0, 0);
	return (0);
}

int	mandelbrot(void)
{
	t_data	shape;
	t_graph	gr;

	gr.x_max = 2;
	gr.x_min = -3.0;
	gr.y_max = 1.5;
	gr.y_min = -1.5;
	shape.gr = &gr;
	shape.mlx = mlx_init();
	init_man(&shape);
	drawing_mandelbort(&shape);
	mlx_hook(shape.mlx_win, 2, 1L << 0, escape_mand, &shape);
	mlx_hook(shape.mlx_win, 17, 0, close_mandl, &shape);
	mlx_mouse_hook(shape.mlx_win, mouse_hook, &shape);
	mlx_loop(shape.mlx);
	return (0);
}
