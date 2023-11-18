/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2023/11/18 16:09:19 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < mlx->sc_height)
	{
		my_mlx_pixel_put(mlx, ray, i, GREN);
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		my_mlx_pixel_put(mlx, ray, i, BLU);
		i++;
	}
}

t_tex	*get_texture(t_mlx *mlx, int ray_v)
{
	if (ray_v == 1)
	{
		if (mlx->ray->vert_x > mlx->ply->plyr_x)
			return (&mlx->tex_ea);
		else
			return (&mlx->tex_ea);
	}
	else
	{
		if (mlx->ray->horiz_y > mlx->ply->plyr_y)
			return (&mlx->tex_so);
		else
			return (&mlx->tex_so);
	}
}

int	get_color(t_mlx *mlx, int ray_v)
{
	if (ray_v == 1)
	{
		if (mlx->ray->vert_x > mlx->ply->plyr_x)
			return (WHI);
		else
			return (WHI);
	}
	else
	{
		if (mlx->ray->horiz_y > mlx->ply->plyr_y)
			return (GREY);
		else
			return (GREY);
	}
}

void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	t_tex	*tex;
	double	y_t;
	double	x_t;
	int		y;

	tex = get_texture(mlx, mlx->ray->ray_v);
	if (mlx->ray->ray_v == 1)
		x_t = fmod(mlx->ray->vert_y, TILE_SIZE) * tex->width / TILE_SIZE;
	else
		x_t = fmod(mlx->ray->horiz_x, TILE_SIZE) * tex->width / TILE_SIZE;
	y = t_pix;
	while (y < b_pix)
	{
		y_t = (y - t_pix) * tex->height / (b_pix - t_pix);
		// int *color = tex->addr + (int)y_t * tex->width + (int)x_t;
		// my_mlx_pixel_put(mlx, ray, y, *color);
		int	c = get_color(mlx, mlx->ray->ray_v);
		my_mlx_pixel_put(mlx, ray, y, c);
		y++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((mlx->sc_width / 2) / \
	tan(mlx->ply->fov_rd / 2));
	b_pix = (mlx->sc_height / 2) + (wall_h / 2);
	t_pix = (mlx->sc_height / 2) - (wall_h / 2);
	draw_wall(mlx, ray, t_pix, b_pix);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
