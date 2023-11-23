/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:26:29 by afatir            #+#    #+#             */
/*   Updated: 2023/11/23 07:40:40 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle >= 2 * M_PI) 
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->dt->map[map_grid_y][map_grid_x] != '1')
	{
		mlx->ply->plyr_x = new_x;
		mlx->ply->plyr_y = new_y;
	}
}

int	ft_release(int key, t_mlx *mlx)
{
	if (key == UP_K || key == DOWN_K)
		mlx->ply->u_d = 0;
	if (key == LEFT_K || key == RIGHT_K)
		mlx->ply->l_r = 0;
	if (key == R_LEFT || key == R_RIGHT)
		mlx->ply->rot = 0;
	return (0);
}

int	ft_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		ft_exit(mlx);
	if (key == UP_K)
		mlx->ply->u_d = 1;
	if (key == DOWN_K)
		mlx->ply->u_d = -1;
	if (key == RIGHT_K)
		mlx->ply->l_r = 1;
	if (key == LEFT_K)
		mlx->ply->l_r = -1;
	if (key == R_RIGHT)
		mlx->ply->rot = 1;
	if (key == R_LEFT)
		mlx->ply->rot = -1;
	return (0);
}

void	cub_hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player(mlx, 0);
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
	move_player(mlx, move_x, move_y);
}
