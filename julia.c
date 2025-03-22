/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:27:23 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/21 18:27:25 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "fractol.h"
#define HEIGHT 1920
#define WIDTH 1080


void	my_mlx_pixel_put_julia(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int rgb_julia(int i)
{
	int r;
	int g;
	int b;
  // i = 30;
	r = (i * 19 ) % 256; // 58
	g = (i * 10) % 256; // 44
	b = (i * 8) % 256; // 240
	return (r * 65536 + g * 256 + b); // 58 * 65536 + 44* 256 + 240 //
}




void	draw_julia(t_data *shap)
{
	double x;
	double y;
	double zx;
	double zy;
	double zr;
	double zi;
	int	i;
	int	i_max;
	y = 0;
	i_max = 100.0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			zy = shap->gr->y_min + y / WIDTH * (shap->gr->y_max - shap->gr->y_min);
			zx = shap->gr->x_min + x / HEIGHT * (shap->gr->x_max - shap->gr->x_min);
			i = 0.0;
			while (zx * zx + zy * zy < 4 && i < i_max)
			{
				zr = (zx * zx) - (zy * zy) + shap->gr->cx;
				zi = 2 * zx * zy + shap->gr->cy;
				zx = zr;
				zy = zi;
				// printf("i ==> %d\n", i);
				i++;
			}
			if (i == i_max)
				my_mlx_pixel_put_julia(shap, x, y, 0x000000);
			else
				my_mlx_pixel_put_julia(shap, x, y, rgb_julia(i));
			// printf("x ==> %f, y ==> %f\n", cx, cy);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(shap->mlx, shap->mlx_win, shap->img, 0, 0);
}
int	mouse_hook_julia( int button,int x, int y, void *param)
{
	(void)x;
	(void)y;
	t_data *shape = (t_data *)param;
	if(!shape)
		return (0);
	if(button == 5)
	{
		printf("scroll down\n");
		shape->gr->x_max = shape->gr->x_max * 1.2;
		shape->gr->x_min *= 1.2;
		shape->gr->y_max *= 1.2;
		shape->gr->y_min *= 1.2;
		// printf("param = %f\n", shape->gr->x_min);
	}
	else if (button == 4)
	{
		printf("scroll up\n");
		shape->gr->x_max =shape->gr->x_max / 1.2;	
		shape->gr->x_min /= 1.2;
		shape->gr->y_max /= 1.2;
		shape->gr->y_min /= 1.2;
		// eprintf("param = %f\n", shape->grx_min);
	}
	// drawing_mandelbort(shape);
	// printf("%f\n", shape->gr->cx);
	draw_julia(shape);
	mlx_put_image_to_window(shape->mlx, shape->mlx_win, shape->img, 0, 0);
	return (0);
}

int	close_julia(int keycode,t_data *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(1);
	}

	printf("keycode is ==> %d\n", keycode);
	return (0);
}



int julia(double a, double b)
{
	t_data shape;
	t_graph gr;

	//********************* */
	gr.x_max = 2;
	gr.x_min = -3.0;
	gr.y_max = 1.5;
	gr.y_min = -1.5;
	gr.cx = a;
	gr.cy = b;
	shape.gr = &gr;
	
	shape.mlx = mlx_init();
	shape.mlx_win = mlx_new_window(shape.mlx, 1920, 1080, "TEST3");
	shape.img = mlx_new_image(shape.mlx, 1920, 1080);
	shape.addr = mlx_get_data_addr(shape.img, &shape.bits_per_pixel, &shape.line_length, &shape.endian);
	//********************* */

	draw_julia(&shape);
	//********************* */
	
	mlx_hook(shape.mlx_win, 2, 1L<<0,close_julia, &shape);
	
	mlx_mouse_hook(shape.mlx_win, mouse_hook_julia, &shape);
	
	mlx_loop(shape.mlx);
	return (0);
}