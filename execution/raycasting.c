/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:36:01 by afatir            #+#    #+#             */
/*   Updated: 2023/11/28 21:23:36 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else 
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y >= S_H || x >= S_W || (y_m >= mlx->dt->h_map || \
	x_m >= mlx->dt->w_map)))
		return (0);
	if (mlx->dt->map2d[y_m] && x_m <= (int)ft_strlen(mlx->dt->map2d[y_m]))
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	unit_circle(float angle, char c)
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

float	get_h_inter(t_mlx *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl); 
	h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || \
		(!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + \
	pow(h_y - mlx->ply->plyr_y, 2)));
}

float	get_v_inter(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || \
		(!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + \
	pow(v_y - mlx->ply->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	draw_map_tile2d(mlx);
	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (ray < S_W)
	{
		mlx->ray->ray_v = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		if (v_inter < h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->ray_v = 1;
		}
		// render_wall(mlx, ray);
		draw_ray_2d(mlx, mlx->ray->ray_ngl, mlx->ray->distance, RED);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W);
	}
}
