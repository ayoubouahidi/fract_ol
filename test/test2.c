#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

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
	double	i;
	double y0 = 500;
	double x0 = 500;
	double r = 150;
	double x;
	t_data img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "AYOUB OUAHIDI hHhHhHhHh");
	img.img =mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);

	i = y0 -r;
	while (i <= y0 + r)
	{
		// x = sqrt(r * r - (i - y0) * (i - y0)) + x0;
		// my_mlx_pixel_put(&img, x, i, 0x00FF0000);	
		// printf("hey");
		// i = i + 0.1;
		if (r * r - (i - y0) * (i - y0) >= 0) {
            x = sqrt(r * r - (i - y0) * (i - y0)) + x0;
            my_mlx_pixel_put(&img, x, i, 0x00FF0000); 

            x = -sqrt(r * r - (i - y0) * (i - y0)) + x0;
            my_mlx_pixel_put(&img, x, i, 0x00FF0000);
        }
        i = i + 0.1;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}