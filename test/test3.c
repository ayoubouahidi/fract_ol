#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int 	mw;
	int		mh;
	int		speed;
}				t_vars;


void reset(t_vars *var){
	if (var->mw > (var->width - var->speed))
		var->mw = 0;
	else if (var->mw < var->speed)
		var->mw = var->width;
	if (var->mh > (var->height - var->speed))
		var->mh = 0;
	else if (var->mh < var->speed)
		var->mh = var->height;
}

double redirect_y(t_vars *var, double y){
	if (y > var->height)
		y -= var->height;
	return (y);
}
double redirect_x(t_vars *var, double x){
	if (x > var->width)
		x -= var->width;
	return (x);
}

int	close(int keycode,t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	if(keycode == 65361)
	{
		vars->mw -= vars->speed, printf("left %d\n", vars->mw);
		draw_line_hor()
	}
	
	// move(vars);
	reset(vars);
	printf("keycode is ==> %d\n", keycode);
	return (0);
}



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	draw_line_from_equation(t_data *data , t_vars *vars, double x_start, double x_end, double m, double b, double color)
// {	
// 	double x;
// 	double y;

// 	x = x_start;
// 	y = 0;
// 	while  (x < x_end)
// 	{
// 		y = m * x + b;  
// 		my_mlx_pixel_put(data, redirect_x(vars, x), redirect_y(vars, x), color); 
// 		printf("test is done\n");
// 		x++;
// 	}
// }
// void	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
// {
// 	int dx = abs(x2 - x1);
// 	int dy = abs(y2 - y1);
// 	int sx = (x1 < x2) ? 1 : -1;
// 	int sy = (y1 < y2) ? 1 : -1;
// 	int err = dx - dy;
	
// 	while (1)
// 	{
// 		my_mlx_pixel_put(data, x1, y1, color);  // Plot the point

// 		if (x1 == x2 && y1 == y2)
// 			break;

// 		int e2 = err * 2;

// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }

void	draw_line_hor(t_data *shape, t_vars *vars, int start, int end, int pos, int color)
{
	int i;
	i = start;
	while (i <= end)
	{
		my_mlx_pixel_put(shape, redirect_x(vars, i), redirect_y(vars, pos), color);
		i++;
	}
}


int main()
{
	t_vars data;
	t_data shape;
	// int i;
	// int j;
	data.mh = 0;
	data.mw = 0;
	data.width = 1920; 
	data.height = 1080;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "TEST3");
	shape.img = mlx_new_image(data.mlx, 1920, 1080);
	shape.addr = mlx_get_data_addr(shape.img, &shape.bits_per_pixel, &shape.line_length, &shape.endian);
	// // while (i < 200)
	// // {
		// // 	printf("test");
		// // 	j = 2 * i + 100;
		// // 	my_mlx_pixel_put(&shape, i , j, 0x00FF0000);
		// // 	i++;
		// // }
		// for (int i = 0; i < 1920 * 1080; i++)
		// 	((unsigned int*)shape.addr)[i] = 0xFFFFFF;
		// draw_line_from_equation(&shape, 100, 700, 2, 100, 0xFF0000);
		// draw_line(&shape, 100, 100, 700, 500, 0xFF0000);  // Red color
	data.speed = 50;
	draw_line_hor(&shape, &data, 100, 700, 500, 0xFF0000);
	mlx_put_image_to_window(data.mlx, data.win, shape.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0,close, &data);
	mlx_loop(data.mlx);
}