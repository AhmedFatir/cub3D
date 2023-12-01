/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:30:47 by afatir            #+#    #+#             */
/*   Updated: 2023/12/01 04:55:40 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_angle(t_mlx *mlx)
{
	char	c;

	c = mlx->dt->map2d[mlx->dt->p_y][mlx->dt->p_x];
	if (c == 'N')
		mlx->ply->angle = 3 * M_PI / 2;
	if (c == 'S')
		mlx->ply->angle = M_PI / 2;
	if (c == 'E')
		mlx->ply->angle = 0;
	if (c == 'W')
		mlx->ply->angle = M_PI;
	mlx->ply->plyr_x = (mlx->dt->p_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx->ply->plyr_y = (mlx->dt->p_y * TILE_SIZE) + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI / 180);
}

void	draw_map_tile2d(t_mlx *mlx)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;
	char	c;

	y = 0;
	y_p = 0;
	while (y < mlx->dt->h_map)
	{
		x = 0;
		x_p = 0;
		while (mlx->dt->sq_map[y][x])
		{
			c = mlx->dt->sq_map[y][x];
			draw_win(mlx, x_p, y_p, WHI);
			if (c == '1')
				draw_win(mlx, x_p, y_p, GREY);
			x++;
			x_p += TILE_SIZE;
		}
		y++;
		y_p += TILE_SIZE;
	}
	draw_player(mlx, mlx->ply->plyr_x, mlx->ply->plyr_y, ORNG);
}

void	draw_win(t_mlx *mlx, int x, int y, int color)
{
	int		x_m;
	int		y_m;
	int		flag;

	y_m = y;
	flag = 0;
	x_m = x;
	while (y_m < (y + TILE_SIZE))
	{
		while (x_m < (x + TILE_SIZE))
			my_mlx_pixel_put(mlx, x_m++, y_m, color);
		y_m++;
		x_m = x;
	}
}

void	draw_player(t_mlx *mlx, int x_p, int y_p, int color)
{
	int		x;
	int		y;
	int		r;

	r = TILE_SIZE / 3;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (pow(x, 2) + pow(y, 2) <= pow(r, 2))
				my_mlx_pixel_put(mlx, x_p + x, y_p + y, color);
			x++;
		}
		y++;
	}
}

void	draw_ray_2d(t_mlx *mlx, double angle, double distance, int color)
{
	double	x;
	double	y;
	int		t;

	t = 0;
	y = mlx->ply->plyr_y;
	x = mlx->ply->plyr_x;
	while (t < distance)
	{
		my_mlx_pixel_put(mlx, (int)x, (int)y, color);
		x += 1 * cos(angle);
		y += 1 * sin(angle);
		t++;
	}
}
