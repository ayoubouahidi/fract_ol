#include "../minilibx-linux/mlx.h"
#include <math.h>
#define key_w 66
#define M_PI 3.14159265358979323846
#include <stdio.h>

// int	key_hook(void *param)
// {
// 	if (key_w == param)

// }

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main()
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int j;
	int i;

	i = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "AYOUB OUAHIDI hHhHhHhHh");
	img.img =mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	//square
	// while (i < 200)
	// { 	
	// 	j = 0;
	// 	while (j < 200)
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, 0x00FF0000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	//cercle 
	while(i < 360)
	{
		j = i * (M_PI / 180);
		my_mlx_pixel_put(&img,960 + (int)(100 * cos(j)),540 + (int)(100 * sin(j)), 0x00FF0000);
		i++;
	}
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}