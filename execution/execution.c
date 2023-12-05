/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/12/05 09:18:31 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drow_map_pixel(void *mlxl)
{
	t_mlx	*mlx;

	mlx = mlxl;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	cub_hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

int	checkload(t_txtr *list)
{
	t_txtr			*tmp;
	mlx_texture_t	*texture;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "NO", 2) || !ft_strncmp(tmp->key, "SO", 2) \
		|| !ft_strncmp(tmp->key, "WE", 2) || !ft_strncmp(tmp->key, "EA", 2))
		{
			texture = mlx_load_png(tmp->value);
			if (texture == NULL)
				return (0);
			mlx_delete_texture(texture);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	load_texture(t_tex *tex, t_txtr *l_ture)
{
	t_txtr		*tmp;

	tmp = l_ture;
	if (!checkload(l_ture))
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "NO", 2))
			tex->no = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "SO", 2))
			tex->so = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "WE", 2))
			tex->we = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "EA", 2))
			tex->ea = mlx_load_png(tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

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

int	execution(t_data *dt)
{
	t_mlx	mlx;

	if (S_H > 1440 || S_W > 2560 || FOV >= 180 || FOV <= 0)
		return (freelist(&dt->t), free_map(dt), 0);
	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	mlx.dt = dt;
	mlx.mlx_p = mlx_init(S_W, S_H, "cub3D", false);
	if (!mlx.mlx_p)
		return (ft_exit(&mlx), 0);
	if (!load_texture(mlx.tex, dt->t))
		return (ft_exit(&mlx), 0);
	get_angle(&mlx);
	mlx_key_hook(mlx.mlx_p, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx_p, &drow_map_pixel, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
	return (0);
}
