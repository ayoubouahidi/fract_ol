#include "../minilibx-linux/mlx.h"

#define key_w 66

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

int main()
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "AYOUB OUAHIDI hHhHhHhHh");
	mlx_new_image(mlx, 1920, 1080);
	// mlx_loop(mlx);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
}