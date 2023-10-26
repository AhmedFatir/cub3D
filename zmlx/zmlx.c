#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WITH 1000
#define HIGT 500
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_pixel(t_data *img, void *mlx, void *mlx_win, int x, int y)
{
	if (x < 0 || x > WITH || y < 0 || y > HIGT)
	{
		printf("NTCHAWFO\n");
		exit(0);
	}
	my_mlx_pixel_put(img, x, y, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}

void devide_win(t_data *img,void *mlx, void *mlx_win)
{
	int x = WITH;
	int y = HIGT / 2;
	int i = 0;
	while (i < x)
		put_pixel(img, mlx, mlx_win, x - i++, y);
	i = (HIGT / 2) * -1;
	while (i < y)
		put_pixel(img, mlx, mlx_win, x/2 , y - i++);
}

void draw_pos_right(t_data *img,void *mlx, void *mlx_win, int x, int y)
{
	int	x_p, x_m;
	int	y_p = y;
	while (y_p < (y+10))
	{
		x_p = x;
		while (x_p < (x+10))
			put_pixel(img, mlx, mlx_win, x_p++, y_p);
		y_p++;
	}
	y_p = y;
	while (y_p > (y-10))
	{
		x_p = x;
		while (x_p < (x+10))
			put_pixel(img, mlx, mlx_win, x_p++, y_p);
		y_p--;
	}
	// mlx_clear_window(mlx, mlx_win);
}
void draw_pos_left(t_data *img,void *mlx, void *mlx_win, int x, int y)
{
	int	x_m;
	int	y_m = y;
	while (y_m > (y-10))
	{
		x_m = x;
		while (x_m > (x-10))
			put_pixel(img, mlx, mlx_win, x_m--, y_m);
		y_m--;
	}
	y_m = y;
	while (y_m < (y+10))
	{
		x_m = x;
		while (x_m > (x-10))
			put_pixel(img, mlx, mlx_win, x_m--, y_m);
		y_m++;
	}
	// mlx_clear_window(mlx, mlx_win);
}
int	ft_exit(int key, t_mlx *mlx)
{
	if (key == 53)
		exit(0);
	if (key == 123)
	{
		mlx_clear_window(mlx->mlxp, mlx->win);
		mlx->x = mlx->x - 10;
		draw_pos_left(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
	}
	if (key == 124)
	{
		mlx_clear_window(mlx->mlxp, mlx->win);
		mlx->x = mlx->x + 10;
		draw_pos_right(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
	}
	if (key == 125)
	{
		mlx_clear_window(mlx->mlxp, mlx->win);
		mlx->y += 10;
		draw_pos_right(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
		draw_pos_left(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
	}
	if (key == 126)
	{
		mlx_clear_window(mlx->mlxp, mlx->win);
		mlx->y -= 10;
		draw_pos_right(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
		draw_pos_left(mlx->dt, mlx->mlxp, mlx->win, mlx->x, mlx->y);
	}
	// devide_win(mlx->dt, mlx->mlxp, mlx->win);
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx.dt = &img;
	/////////////////////////////////////////////
	mlx.x = WITH / 2;
	mlx.y = HIGT / 2;
	// devide_win(mlx.dt, mlx.mlxp, mlx.win);
	draw_pos_right(mlx.dt, mlx.mlxp, mlx.win, mlx.x, mlx.y);
	draw_pos_left(mlx.dt, mlx.mlxp, mlx.win, mlx.x, mlx.y);
	
		

	///////////////////////////////////////////////
	mlx_hook(mlx.win, 2, 0, ft_exit, &mlx);
	mlx_loop(mlx.mlxp);
}