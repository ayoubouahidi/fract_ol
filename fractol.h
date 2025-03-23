/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:46:08 by ayouahid          #+#    #+#             */
/*   Updated: 2025/03/19 23:46:09 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include "fractol.h"
# define HEIGHT 1920
# define WIDTH 1080

typedef struct s_graph
{
	double	x_min;
	double	x_max;
	double	y_max;
	double	y_min;
	double	cx;
	double	cy;
}	t_graph;

typedef struct s_data
{
	void	*img;
	char	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_graph	*gr;
}	t_data;

int		mandelbrot(void);
int		julia(double a, double b);
int		lenght(char *av);	
int		ft_isdigit(int a);
size_t	ft_strlen(const char *a);
int		ft_strcmp(char *s1, char *s2);
int		isvalid(char *str);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		rgb(int i);
int		i_equalt_to(double zx, double zy, int i_max, t_data *shap);
void	init_man(t_data *shape);
int		close_mandl(t_data *vars);
void	my_mlx_pixel_put_julia(t_data *data, int x, int y, int color);
int		rgb_julia(int i);
int		i_equalt_to_j(double zx, double zy, int i_max, t_data *shap);
void	draw_julia(t_data *shap);
int		mouse_hook_julia( int button, int x, int y, void *param);

#endif