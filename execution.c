/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/25 17:43:47 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_mlx *mlx)
{
	int		i;

	i = 1;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	ft_free_data(mlx->dt, NULL, &i, 0);
	free(mlx->ply);
	free(mlx->ray);
	print_error("Game closed\n", &i);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0)
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

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

void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.dt = dt;
	get_h_w(&mlx);
	mlx.mlx_p = mlx_init(S_W, S_H, "cub3D", false);
	get_angle(&mlx);
	mlx_key_hook(mlx.mlx_p, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx_p, &drow_map_pixel, &mlx);
	mlx_loop(mlx.mlx_p);
	mlx_terminate(mlx.mlx_p);
	ft_exit(&mlx);
}
