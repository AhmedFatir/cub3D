/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/12/01 23:49:21 by afatir           ###   ########.fr       */
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

void	my_mouse(void *param)
{
	t_mlx		*mlx;
	static int	fix;

	mlx = param;
	if (fix++ == 0)
		mlx->ply->m_x = S_W / 2;
	mlx_get_mouse_pos(mlx->mlx_p, &mlx->ply->m_x, &mlx->ply->m_y);
	mlx->ply->angle += (float)(mlx->ply->m_x - (S_W / 2)) / (S_H / 2);
	mlx_set_mouse_pos(mlx->mlx_p, (S_W / 2), (S_H / 2));
}

int	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	mlx.dt = dt;
	if (S_H > 1440 || S_W > 2560 || FOV > 180 || FOV < 0)
		return (ft_exit(&mlx), 0);
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
