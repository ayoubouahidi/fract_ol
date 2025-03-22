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

int	close(int keycode,t_data *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(1);
	}

	printf("keycode is ==> %d\n", keycode);
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
  // i = 30;
	r = (i * 19 ) % 256; // 58
	g = (i * 10) % 256; // 44
	b = (i * 8) % 256; // 240
	return (r * 65536 + g * 256 + b); // 58 * 65536 + 44* 256 + 240 //
}

void	drawing_mandelbort(t_data *shap)
{
	double x;
	double y;
	double cx;
	double cy;
	double zx;
	double zy;
	double zr;
	double zi;
	int	i;
	int	i_max;

	y = 0;
	i_max = 100.0;
	// printf("xmin ==> %f\n ",shap->x_min);
	while (y < WIDTH)
	{
		cy = shap->gr->y_min + y / WIDTH * (shap->gr->y_max - shap->gr->y_min); 
		x = 0;
		while (x < HEIGHT)
		{
			cx = shap->gr->x_min + x / HEIGHT * (shap->gr->x_max - shap->gr->x_min);
			zx = 0.0;
			zy = 0.0;
			i = 0.0;
			while (zx * zx + zy * zy < 4 && i < i_max)
			{
				zr = (zx * zx) - (zy * zy) + cx;
				zi = 2 * zx * zy + cy;
				zx = zr;
				zy = zi;
				// printf("i ==> %d\n", i);
				i++;
			}
			if (i == i_max)
				my_mlx_pixel_put(shap, x, y, 0x000000);
			else
				my_mlx_pixel_put(shap, x, y, rgb(i));
			// printf("x ==> %f, y ==> %f\n", cx, cy);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(shap->mlx, shap->mlx_win, shap->img, 0, 0);
}

// void	julia(t_data *shap,double cx, double cy)
// {
// 	double x;
// 	double y;
// 	double zx;
// 	double zy;
// 	double zr;
// 	double zi;
// 	int	i;
// 	int	i_max;
// 	y = 0;
// 	i_max = 100.0;
// 	while (y < WIDTH)
// 	{
// 		x = 0;
// 		while (x < HEIGHT)
// 		{
// 			zy = shap->gr->y_min + y / WIDTH * (shap->gr->y_max - shap->gr->y_min);
// 			zx = shap->gr->x_min + x / HEIGHT * (shap->gr->x_max - shap->gr->x_min);
// 			i = 0.0;
// 			while (zx * zx + zy * zy < 4 && i < i_max)
// 			{
// 				zr = (zx * zx) - (zy * zy) + cx;
// 				zi = 2 * zx * zy + cy;
// 				zx = zr;
// 				zy = zi;
// 				// printf("i ==> %d\n", i);
// 				i++;
// 			}
// 			if (i == i_max)
// 				my_mlx_pixel_put(shap, x, y, 0x000000);
// 			else
// 				my_mlx_pixel_put(shap, x, y, rgb(i));
// 			// printf("x ==> %f, y ==> %f\n", cx, cy);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(shap->mlx, shap->mlx_win, shap->img, 0, 0);
// }

int	mouse_hook( int button,int x, int y, void *param)
{
	(void)x;
	(void)y;
	t_data *shape = (t_data *)param;
	if(!shape)
		return (0);
	if(button == 5)
	{
		printf("scroll down\n");
		shape->gr->x_max =shape->gr->x_max * 1.2;
		shape->gr->x_min *= 1.2;
		shape->gr->y_max *= 1.2;
		shape->gr->y_min *= 1.2;
		printf("param = %f\n", shape->gr->x_min);
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
	drawing_mandelbort(shape);
	// julia(shape, 0.87, 0.27015);
	mlx_put_image_to_window(shape->mlx, shape->mlx_win, shape->img, 0, 0);
	return (0);
}

int mandelbrot()
{
	// t_vars data;
	t_data shape;
	t_graph gr;
	double cx =  -0.7;
	double cy = 0.27015;
	//********************* */
	gr.x_max = 2;
	gr.x_min = -3.0;
	gr.y_max = 1.5;
	gr.y_min = -1.5;
	shape.gr = &gr;
	
	shape.mlx = mlx_init();
	shape.mlx_win = mlx_new_window(shape.mlx, 1920, 1080, "TEST3");
	shape.img = mlx_new_image(shape.mlx, 1920, 1080);
	shape.addr = mlx_get_data_addr(shape.img, &shape.bits_per_pixel, &shape.line_length, &shape.endian);
	//********************* */
	
	drawing_mandelbort(&shape);
	// julia(&shape , cx, cy);
	//********************* */
	
	mlx_hook(shape.mlx_win, 2, 1L<<0,close, &shape);
	
	mlx_mouse_hook(shape.mlx_win, mouse_hook, &shape);
	
	mlx_loop(shape.mlx);
	return (0);
}