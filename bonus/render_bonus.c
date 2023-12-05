/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2023/12/05 09:08:36 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_floor_ceiling_bonus(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int		i;
	int		c;

	i = b_pix;
	c = get_rgba_bonus(ft_atoi(mlx->dt->ff[0]), ft_atoi(mlx->dt->ff[1]), \
		ft_atoi(mlx->dt->ff[2]), 255);
	while (i < S_H)
		my_mlx_pixel_put_bonus(mlx, ray, i++, c);
	i = 0;
	c = get_rgba_bonus(ft_atoi(mlx->dt->cc[0]), ft_atoi(mlx->dt->cc[1]), \
		ft_atoi(mlx->dt->cc[2]), 255);
	while (i < t_pix)
		my_mlx_pixel_put_bonus(mlx, ray, i++, c);
}

mlx_texture_t	*get_texture_bonus(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle_bonus(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->tex->ea);
		else
			return (mlx->tex->we);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->tex->so);
		else
			return (mlx->tex->no);
	}
}

double	get_x_o_bonus(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->horiz_x * \
		(texture->width / TILE_SIZE_R)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vert_y * \
		(texture->width / TILE_SIZE_R)), texture->width);
	return (x_o);
}

void	draw_wall_bonus(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			y_step;

	texture = get_texture_bonus(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	y_step = (double)texture->height / wall_h;
	x_o = get_x_o_bonus(texture, mlx);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * y_step;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put_bonus(mlx, mlx->ray->index, t_pix, reverse_bytes_bonus \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += y_step;
		t_pix++;
	}
}

void	render_wall_bonus(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle_bonus \
	(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE_R / mlx->ray->distance) * ((S_W / 2) / \
	tan(mlx->ply->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall_bonus(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling_bonus(mlx, ray, t_pix, b_pix);
}
