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

# include "./ft_printf/ft_printf.h"

typedef struct s_graph {
	double	x_min;
	double	x_max;
	double	y_max;
	double	y_min;
	double 	cx;
	double 	cy;
}			t_graph;

typedef struct	s_data {
	void	*img;
	char	*addr;
	void 	*mlx;
	void 	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_graph *gr;
}				t_data;

int	mandelbrot();
int julia();
// typedef struct s_vars
// {
// 	void *mlx;
// 	void *mlx_win;
// }				t_vars;
