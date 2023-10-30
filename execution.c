/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/10/30 13:22:23 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (y > (SIZE_H * mlx->gm->map_h) || x < 0 || x > (SIZE_W * mlx->gm->map_w) || y < 0 || y > (SIZE_H * mlx->gm->map_h))
	{
		ft_printf ("NTCHAWFO\n");
		exit(0);
	}
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 1;
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	print_error("Game closed\n", &i);
	ft_free_data(mlx->gm->dt, NULL, &i, 0);
	free(mlx->gm);
	exit(0);
	return (0);
}


void draw_win(t_mlx *mlx, int x, int y, int color)
{
	int	x_m;
	int	y_m = y;
	int		flag;
	flag = 0;
	while (y_m < (y+SIZE_H))
	{
		x_m = x;
		if (!flag)
		{	
			while (x_m < (x+SIZE_W))
				my_mlx_pixel_put(mlx, x_m++, y_m, BLK);
			flag = 1;
		}
		else
		{		
			while (x_m < (x+SIZE_W))
				my_mlx_pixel_put(mlx, x_m++, y_m, color);
			my_mlx_pixel_put(mlx, x_m-1, y_m, BLK);
		}
		y_m++;
	}
}

void drow_player(t_mlx *mlx, int x_p, int y_p, char c, int color)
{
	int		x;
	int		y;

	y = SIZE_H/4;
	mlx->gm->plyr_x = x_p;
	mlx->gm->plyr_y = y_p;
	while (y < (SIZE_H - SIZE_H/4))
	{
		x = SIZE_W/4;
		while (x < (SIZE_W - SIZE_W/4))
			my_mlx_pixel_put(mlx, x_p + x++, y_p + y, color);
		y++;
	}
	y = SIZE_H/2;
	x = SIZE_W/2;
	if (c == 'N')
	{
		while (y > (SIZE_H/2 * -1))
			my_mlx_pixel_put(mlx, x_p + x, y_p + y--, RED);
	}
}

void	drow_map_pixel(t_mlx *mlx, int flag)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;

	y = 0;
	y_p = 0;
	while (y < mlx->gm->map_h)
	{
		x = 0;
		x_p = 0;
		while (mlx->gm->dt->map[y][x])
		{
			char c = mlx->gm->dt->map[y][x];
			if (c == '1')
				draw_win(mlx, x_p, y_p, GREY);
			else if (c == '0' || is_sep(c))
				draw_win(mlx, x_p, y_p, WHI);
			else if (valide_symbols(c) == 2)
			{
				draw_win(mlx, x_p, y_p, WHI);
				if (!flag)
					drow_player(mlx, x_p, y_p, c, ORNG);
			}
			x++;
			x_p += SIZE_W;
		}
		y++;
		y_p += SIZE_H;
	}
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->gm->img, 0, 0);
}

int	cub_hook(t_mlx *mlx, t_data *dt, int key)
{
	if (key == -1)
		return (0);
	if (key == LEFT_K)
		mlx->gm->plyr_x -= 4;
	else if (key == RIGHT_K)
		mlx->gm->plyr_x += 4;
	else if (key == DOWN_K)
		mlx->gm->plyr_y += 4;
	else if (key == UP_K)
		mlx->gm->plyr_y -= 4;
	drow_map_pixel(mlx, 1);
	// if (mlx->gm->plyr_y >= (SIZE_H * mlx->gm->map_h))
	// 	exit(0);
	ft_printf ("%d-------%d\n", mlx->gm->plyr_y, mlx->gm->plyr_x);
	drow_player(mlx, mlx->gm->plyr_x, mlx->gm->plyr_y, dt->map[dt->p_x][dt->p_y], ORNG);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->gm->img, 0, 0);
	return (0);
}

int	ft_hook(int key,t_mlx *mlx)
{
	if (key == 53)
		ft_exit(mlx);
	else
		cub_hook(mlx, mlx->gm->dt, key);
	return (0);
}

void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.gm = (t_game *)ft_calloc(sizeof(t_game), 1);
	mlx.gm->dt = dt;
	mlx.mlx_p = mlx_init();
	get_h_w(mlx.gm);
	mlx.win = mlx_new_window(mlx.mlx_p, (mlx.gm->map_w * SIZE_H), (mlx.gm->map_h * SIZE_W), "cub3D");
	mlx.gm->img = mlx_new_image(mlx.mlx_p, (mlx.gm->map_w * SIZE_H), (mlx.gm->map_h * SIZE_W));
	mlx.addr = mlx_get_data_addr(mlx.gm->img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	drow_map_pixel(&mlx, 0);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}
