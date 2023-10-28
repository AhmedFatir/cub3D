/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/10/28 12:05:09 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_h_w(t_game *mlx)
{
	int		i;

	i = 0; 
	mlx->map_h = getmap_hi(mlx->dt->map);
	mlx->map_w = 0;
	while (i < mlx->map_h)
	{
		if ((int)ft_strlen(mlx->dt->map[i]) > mlx->map_w)
			mlx->map_w = (int)ft_strlen(mlx->dt->map[i]);
		i++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 1;
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	print_error("Game closed\n", &i);
	ft_free_data(mlx->gm->dt, NULL, &i, 0);
	free(mlx->gm);
	exit(0);
	return (0);
}

int	ft_hook(int key,t_mlx *mlx)
{
	if (key == 53)
		ft_exit(mlx);
	else
		drow_map(mlx, key);
	return (0);
}

void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.gm = (t_game *)ft_calloc(sizeof(t_game), 1);
	mlx.gm->dt = dt;
	mlx.mlx_p = mlx_init();
	get_h_w(mlx.gm);
	mlx.win = mlx_new_window(mlx.mlx_p, (mlx.gm->map_w * SIZE_H), (mlx.gm->map_h * SIZE_W), "cub3D");
	mlx.gm->img = mlx_new_image(mlx.mlx_p, (mlx.gm->map_w * SIZE_H), (mlx.gm->map_h * SIZE_W));
	mlx.addr = mlx_get_data_addr(mlx.gm->img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	drow_map(&mlx, -1);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}
