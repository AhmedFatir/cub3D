/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2023/11/29 18:00:18 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < S_H)
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

mlx_texture_t	*get_texture(t_mlx *mlx, int ray_v)
{
	if (ray_v == 1)
	{
		if (mlx->ray->vert_x > mlx->ply->plyr_x)
			return (mlx->tex->ea);
		else
			return (mlx->tex->ea);
	}
	else
	{
		if (mlx->ray->horiz_y > mlx->ply->plyr_y)
			return (mlx->tex->so);
		else
			return (mlx->tex->so);
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
	int		y;
	int		c;

	y = t_pix;
	while (y < b_pix)
	{
		// if ((y > 0 && y <= S_H) && (ray > 0 && ray <= S_W))
		// {
			c = get_color(mlx, mlx->ray->ray_v);
			my_mlx_pixel_put(mlx, ray, y, c);
		// }
		y++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / \
	tan(mlx->ply->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);

	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
