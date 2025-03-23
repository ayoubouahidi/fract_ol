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

int	close_julia(t_data *vars)
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

int	escape(int keycode, t_data *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 65307)
		close_julia(vars);
	return (0);
}

void	init(t_data *shape)
{
	shape->mlx = mlx_init();
	if (!shape->mlx)
	{
		ft_printf("MLX FAIL");
		exit(1);
	}
	shape->mlx_win = mlx_new_window(shape->mlx, HEIGHT, WIDTH, "JULIA");
	if (!shape->mlx_win)
	{
		ft_printf("MLX FAIL");
		close_julia(shape);
	}
	shape->img = mlx_new_image(shape->mlx, HEIGHT, WIDTH);
	if (!shape->img)
	{
		ft_printf("MLX FAIL");
		close_julia(shape);
	}
	shape->addr = mlx_get_data_addr(shape->img,
			&shape->bits_per_pixel, &shape->line_length, &shape->endian);
	if (!shape->addr)
	{
		ft_printf("MLX FAIL");
		close_julia(shape);
	}
}

int	julia(double a, double b)
{
	t_data	shape;
	t_graph	gr;

	gr.x_max = 2;
	gr.x_min = -3.0;
	gr.y_max = 1.5;
	gr.y_min = -1.5;
	gr.cx = a;
	gr.cy = b;
	shape.gr = &gr;
	init(&shape);
	draw_julia(&shape);
	mlx_hook(shape.mlx_win, 2, 1L << 0, escape, &shape);
	mlx_hook(shape.mlx_win, 17, 0, close_julia, &shape);
	mlx_mouse_hook(shape.mlx_win, mouse_hook_julia, &shape);
	mlx_loop(shape.mlx);
	return (0);
}
