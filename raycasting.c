/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:36:01 by afatir            #+#    #+#             */
/*   Updated: 2023/11/23 02:44:32 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_inter(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (0);
		}
		*step *= -1;
	}
	else 
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (0);
		}
		*step *= -1;
	}
	return (1);
}

int	check_wall(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y >= S_H || x >= S_W || (y_m >= mlx->dt->map_h || x_m >= mlx->dt->map_w)))
		return (0);
	if (mlx->dt->map[y_m] && x_m <= (int)ft_strlen(mlx->dt->map[y_m]))
		if (mlx->dt->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);			
	}
	else if (c == 'y')
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (1);
	}
	return (0);
}

float	get_x_inter(t_mlx *mlx, float angl)
{
	float	x_inter;
	float	y_inter;
	float	x_step;
	float	y_step;
	int		check;

	y_inter = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	y_step = TILE_SIZE;
	check = check_inter(angl, &y_inter, &y_step, 1);
	x_inter = mlx->ply->plyr_x + (y_inter - mlx->ply->plyr_y) / tan(angl);
	x_step = TILE_SIZE / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || \
		(!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (check_wall(x_inter, y_inter - check, mlx))
	{
		x_inter += x_step;
		y_inter += y_step;
	}
	mlx->ray->horiz_x = x_inter;
	mlx->ray->horiz_y = y_inter;
	return (sqrt(pow(x_inter - mlx->ply->plyr_x, 2) + \
	pow(y_inter - mlx->ply->plyr_y, 2)));
}


float	get_y_inter(t_mlx *mlx, float angl)
{
	float	x_inter;
	float	y_inter;
	float	x_step;
	float	y_step;
	int		check;

	x_inter = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
	x_step = TILE_SIZE;
	check = check_inter(angl, &x_inter, &x_step, 0);
	y_inter = mlx->ply->plyr_y + (x_inter - mlx->ply->plyr_x) * tan(angl);
	y_step = TILE_SIZE * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || \
		(!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (check_wall(x_inter - check, y_inter, mlx))
	{
		x_inter += x_step;
		y_inter += y_step;
	}
	mlx->ray->vert_x = x_inter;
	mlx->ray->vert_y = y_inter;
	return (sqrt(pow(x_inter - mlx->ply->plyr_x, 2) + \
	pow(y_inter - mlx->ply->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	double	x_inter;
	double	y_inter;
	int		ray;

	draw_map_tile2d(mlx);
	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (ray < S_W)
	{
		mlx->ray->ray_v = 0;
		x_inter = get_x_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		y_inter = get_y_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		if (y_inter < x_inter)
			mlx->ray->distance = y_inter;
		else
		{
			mlx->ray->distance = x_inter;
			mlx->ray->ray_v = 1;
		}
		// render_wall(mlx, ray);
		draw_ray_2d(mlx, mlx->ray->ray_ngl, mlx->ray->distance, RED);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W);
	}
}
