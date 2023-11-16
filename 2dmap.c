/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:30:47 by afatir            #+#    #+#             */
/*   Updated: 2023/11/16 18:05:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_tile2d(t_mlx *mlx)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;
	char	c;

	y = 0;
	y_p = 0;
	while (y < mlx->dt->map_h)
	{
		x = 0;
		x_p = 0;
		while (mlx->dt->map[y][x])
		{
			c = mlx->dt->map[y][x];
			draw_win(mlx, x_p, y_p, WHI);
			if (c == '1')
				draw_win(mlx, x_p, y_p, GREY);
			x++;
			x_p += TILE_SIZE;
		}
		y++;
		y_p += TILE_SIZE;
	}
	drow_player(mlx, mlx->ply->plyr_x, mlx->ply->plyr_y, ORNG);
}

void	draw_win(t_mlx *mlx, int x, int y, int color)
{
	int		x_m;
	int		y_m;
	int		flag;

	y_m = y;
	flag = 0;
	while (y_m < (y + TILE_SIZE))
	{
		x_m = x;
		if (!flag)
		{
			while (x_m < (x + TILE_SIZE))
				my_mlx_pixel_put(mlx, x_m++, y_m, BLK);
			flag = 1;
		}
		else
		{
			while (x_m < (x + TILE_SIZE))
				my_mlx_pixel_put(mlx, x_m++, y_m, color);
			my_mlx_pixel_put(mlx, x_m - 1, y_m, BLK);
		}
		y_m++;
	}
}

void	drow_player(t_mlx *mlx, int x_p, int y_p, int color)
{
	int		x;
	int		y;

	x_p -= TILE_SIZE / 2;
	y_p -= TILE_SIZE / 2;
	y = TILE_SIZE / 3;
	while (y < (TILE_SIZE - TILE_SIZE / 3))
	{
		x = TILE_SIZE / 3;
		while (x < (TILE_SIZE - TILE_SIZE / 3))
			my_mlx_pixel_put(mlx, x_p + x++, y_p + y, color);
		y++;
	}
}

void	map_2d(t_mlx *mlx, int raw_distance_to_wall)
{
	float	s_x;
	float	s_y;
	float	t;

	mlx->ray->ray_x = cos(mlx->ray->ray_ngl) * RAY_STEP;
	mlx->ray->ray_y = sin(mlx->ray->ray_ngl) * RAY_STEP;
	s_x = mlx->ply->plyr_x;
	s_y = mlx->ply->plyr_y;
	t = 0;
	while (t < raw_distance_to_wall)
	{
		my_mlx_pixel_put(mlx, (int)s_x, (int)s_y, RED);
		s_x += mlx->ray->ray_x;
		s_y += mlx->ray->ray_y;
		t += RAY_STEP;
	}
}
