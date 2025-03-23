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

int close_mandl(t_data *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

int escape_mand(int keycode, t_data *vars)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (keycode == 65307)
		close_mandl(vars);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int rgb(int i)
{
	int r;
	int g;
	int b;

	r = (i * 19 ) % 256; 
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
	return(i);
}
void	drawing_mandelbort(t_data *shap)
{
	double (x), (y), (zx), (zy);
	int	(i), (i_max);

	y = 0;
	i_max = 100.0;
	while (y < WIDTH)
	{
		shap->gr->cy = shap->gr->y_min + y / WIDTH * (shap->gr->y_max - shap->gr->y_min); 
		x = 0;
		while (x < HEIGHT)
		{
			shap->gr->cx = shap->gr->x_min + x / HEIGHT * (shap->gr->x_max - shap->gr->x_min);
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


int	mouse_hook( int button,int x, int y, void *param)
{
	(void)x;
	(void)y;
	t_data *shape = (t_data *)param;
	if(!shape)
		return (0);
	if(button == 5)
	{
		shape->gr->x_max =shape->gr->x_max * 1.2;
		shape->gr->x_min *= 1.2;
		shape->gr->y_max *= 1.2;
		shape->gr->y_min *= 1.2;
	}
	else if (button == 4)
	{
		shape->gr->x_max =shape->gr->x_max / 1.2;	
		shape->gr->x_min /= 1.2;
		shape->gr->y_max /= 1.2;
		shape->gr->y_min /= 1.2;
	}
	drawing_mandelbort(shape);
	mlx_put_image_to_window(shape->mlx, shape->mlx_win, shape->img, 0, 0);
	return (0);
}

int mandelbrot()
{
	t_data shape;
	t_graph gr;

	gr.x_max = 2;
	gr.x_min = -3.0;
	gr.y_max = 1.5;
	gr.y_min = -1.5;
	shape.gr = &gr;
	shape.mlx = mlx_init();
	if(!shape.mlx)
		return(ft_printf("MLX FAIL"), 0);
	shape.mlx_win = mlx_new_window(shape.mlx, 1920, 1080, "MANDELBROT");
	if(!shape.mlx_win)
		return(ft_printf("MLX FAIL"), 0);
	shape.img = mlx_new_image(shape.mlx, 1920, 1080);
	if(!shape.img)
		return(ft_printf("MLX FAIL"), 0);
	shape.addr = mlx_get_data_addr(shape.img, &shape.bits_per_pixel, &shape.line_length, &shape.endian);
	drawing_mandelbort(&shape);
	mlx_hook(shape.mlx_win, 2, 1L << 0, escape_mand, &shape);
	mlx_hook(shape.mlx_win, 17, 0, close_mandl, &shape);
	mlx_mouse_hook(shape.mlx_win, mouse_hook, &shape);	
	mlx_loop(shape.mlx);
	return (0);
}
