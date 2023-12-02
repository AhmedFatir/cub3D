/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:26:29 by afatir            #+#    #+#             */
/*   Updated: 2023/12/02 00:05:40 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	rotate_player_bonus(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void	move_player_bonus(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	map_grid_x = (new_x / TILE_SIZE_R);
	map_grid_y = (new_y / TILE_SIZE_R);
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->dt->sq_map[map_grid_y][mlx->ply->plyr_x / TILE_SIZE_R] != '1' && \
	mlx->dt->sq_map[mlx->ply->plyr_y / TILE_SIZE_R][map_grid_x] != '1'))
	{
		mlx->ply->plyr_x = new_x;
		mlx->ply->plyr_y = new_y;
	}
}

void	cub_hook_bonus(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->rot == 1)
		rotate_player_bonus(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player_bonus(mlx, 0);
	if (mlx->ply->l_r == 1)
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1)
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1)
	{
		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1)
	{
		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player_bonus(mlx, move_x, move_y);
}

void	ft_reles_bonus(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}

void	key_press_bonus(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS \
	|| keydata.action == MLX_REPEAT))
		ft_exit_bonus(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->ply->rot = 1;
	ft_reles_bonus(keydata, mlx);
}
