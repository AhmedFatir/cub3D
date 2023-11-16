#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WITH 1000
#define HIGT 500
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endi;
}				t_data;

typedef struct	s_mlx {
	void	*mlxp;
	void	*win;
	int		x;
	int		y;
	t_data	*dt;
}				t_mlx;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void devide_win(t_mlx *mlx)
{
	int i;
	if ((mlx->x-10) < 0 || (mlx->x+10) > WITH || (mlx->y-10) < 0 || (mlx->y+10) > HIGT)
	{
		printf("NTCHAWFO\n");
		exit(0);
	}
	i = 0;
	while (i < mlx->x)
		my_mlx_pixel_put(mlx->dt, i++, mlx->y, 0xff0000);
	i = WITH;
	while (i > mlx->x)
		my_mlx_pixel_put(mlx->dt, i--, mlx->y, 0xff0000);
	i = 0;
	while (i < mlx->y)
		my_mlx_pixel_put(mlx->dt, mlx->x, i++, 0xff9300);
	i = HIGT;
	while (i > mlx->y)
		my_mlx_pixel_put(mlx->dt, mlx->x, i--, 0xff9300);
}

void draw_win(t_mlx *mlx)
{
	devide_win(mlx);
	int	x_m, x_p;
	int	y_p = mlx->y;
	int	y_m = mlx->y;
	while (y_m > (mlx->y-10) && y_p < (mlx->y+10))
	{
		x_m = mlx->x;
		x_p = mlx->x;
		while (x_m > (mlx->x-10) && x_p < (mlx->x+10))
		{
			my_mlx_pixel_put(mlx->dt, x_m--, y_m, 0x009300);
			my_mlx_pixel_put(mlx->dt, x_p++, y_p, 0x009300);
		}
		y_m--;
		y_p++;
	}
	y_m = mlx->y;
	y_p = mlx->y;
	while (y_m < (mlx->y+10) && y_p > (mlx->y-10))
	{
		x_m = mlx->x;
		x_p = mlx->x;
		while (x_m > (mlx->x-10) && x_p < (mlx->x+10))
		{
			my_mlx_pixel_put(mlx->dt, x_m--, y_m, 0x009300);
			my_mlx_pixel_put(mlx->dt, x_p++, y_p, 0x009300);
		}
		y_m++;
		y_p--;
	}

}

int	ft_exit(int key, t_mlx *mlx)
{
	if (key == 53)
		exit(0);
	else if (key == 123)
		mlx->x -= 5;
	else if (key == 124)
		mlx->x += 5;
	else if (key == 125)
		mlx->y += 5;
	else if (key == 126)
		mlx->y -= 5;
	else 
		return (0);
	mlx_destroy_image(mlx->mlxp, mlx->dt->img);
	mlx->dt->img = NULL;
	mlx->dt->img = mlx_new_image(mlx->mlxp, WITH, HIGT);
	draw_win(mlx);
	mlx_put_image_to_window(mlx->mlxp, mlx->win, mlx->dt->img, 0, 0);
	return (0);
}
int	main(void)
{
	t_data	img;
	t_mlx	mlx;
	int y,x;

	mlx.mlxp = mlx_init();
	mlx.win = mlx_new_window(mlx.mlxp, WITH, HIGT, "Hello world!");
	img.img = mlx_new_image(mlx.mlxp, WITH, HIGT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endi);
	mlx.dt = &img;
	/////////////////////////////////////////////
	mlx.x = WITH / 2;
	mlx.y = HIGT / 2;
	draw_win(&mlx);
	mlx_put_image_to_window(mlx.mlxp, mlx.win, img.img, 0, 0);
	
		

	///////////////////////////////////////////////
	mlx_hook(mlx.win, 2, 0, ft_exit, &mlx);
	mlx_loop(mlx.mlxp);
}