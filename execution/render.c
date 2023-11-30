/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2023/11/30 23:32:39 by afatir           ###   ########.fr       */
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

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
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

int	get_color(t_mlx *mlx, int flag)
{
	if (flag == 1)
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (WHI);
		else
			return (RED);
	}
	else
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (GREY);
		else
			return (ORNG);
	}
}

unsigned int reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix, double wall_h)
{
	int				y;
	int				c;
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;

	y = t_pix;
	texture = get_texture(mlx, mlx->ray->flag);
	uint32_t *arr = (uint32_t *)texture->pixels;
	double y_step = (double)texture->height / wall_h;
	if (mlx->ray->flag == 1)
		x_o = (int)(mlx->ray->horiz_x  * (texture->width / TILE_SIZE_MAP)) % texture->width;
	else
		x_o = (int)(mlx->ray->vert_y  * (texture->width / TILE_SIZE_MAP)) % texture->width;
	y_o = (y - (S_H / 2) + (wall_h / 2)) * y_step;
	if (y_o < 0)
		y_o = 0;
	while (y < b_pix)
	{
		if (y_o >= 0 && y_o < texture->height && x_o >= 0 && x_o < texture->width) {
			c = arr[(int)y_o * texture->width + (int)x_o];
			y_o += y_step;
			my_mlx_pixel_put(mlx, ray, y, reverse_bytes(c));
		} else
			exit (0);
		y++;
	}
}

//--------textures------------
// mlx_texture_t	*get_texture(t_mlx *mlx, float angl)
// {
// 	if (mlx->ray->ray_v)
// 	{
// 		if (angl > 0 && angl < M_PI)
// 			return (mlx->tex->we);
// 		else
// 			return (mlx->tex->ea);
// 	}
// 	else
// 	{
// 		if (angl > M_PI / 2 && angl < 3 * M_PI / 2)
// 			return (mlx->tex->no);
// 		else
// 			return (mlx->tex->so);
// 	}
// 	return (NULL);
// }

uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a << 0);
}

uint32_t ft_get_color(int ofsetx, int ofsety, mlx_texture_t *text)
{
    uint32_t	r;
    uint32_t	g;
    uint32_t	b;
    uint32_t	a;

    a = 255;
	r = text->pixels[(ofsety * (text->width * 4)) + (ofsetx * 4)];
    g = text->pixels[(ofsety * (text->width * 4)) + (ofsetx * 4) + 1];
    b = text->pixels[(ofsety * (text->width * 4)) + (ofsetx * 4) + 2];
    return (get_rgba(r, g, b, a));
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
	draw_wall(mlx, ray, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
