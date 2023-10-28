/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:57:55 by afatir            #+#    #+#             */
/*   Updated: 2023/10/28 12:07:11 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mv_left_and_right(t_data *dt, int i, char c)
{
	if (i == 1)
	{
		dt->map[dt->p_x][dt->p_y] = '0';
		dt->p_y -= 1;
		dt->map[dt->p_x][dt->p_y] = c;
	}
	else if (i == 2)
	{
		dt->map[dt->p_x][dt->p_y] = '0';
		dt->p_y += 1;
		dt->map[dt->p_x][dt->p_y] = c;
	}
	return (0);
}

int	mv_down_and_up(t_data *dt, int i, char c)
{
	if (i == 1)
	{
		dt->map[dt->p_x][dt->p_y] = '0';
		dt->p_x += 1;
		dt->map[dt->p_x][dt->p_y] = c;
	}
	else if (i == 2)
	{
		dt->map[dt->p_x][dt->p_y] = '0';
		dt->p_x -= 1;
		dt->map[dt->p_x][dt->p_y] = c;
	}
	return (0);
}

int	ft_mv(int key, t_data *dt)
{
	if (key == -1)
		return (0);
	if ((key == LEFT_K) && (dt->map[dt->p_x][dt->p_y - 1] == '0'))
		mv_left_and_right(dt, 1, dt->map[dt->p_x][dt->p_y]);
	else if ((key == RIGHT_K) && (dt->map[dt->p_x][dt->p_y + 1] == '0'))
		mv_left_and_right(dt, 2, dt->map[dt->p_x][dt->p_y]);
	else if ((key == DOWN_K) && (dt->map[dt->p_x + 1][dt->p_y] == '0'))
		mv_down_and_up(dt, 1, dt->map[dt->p_x][dt->p_y]);
	else if ((key == UP_K) && (dt->map[dt->p_x - 1][dt->p_y] == '0'))
		mv_down_and_up(dt, 2, dt->map[dt->p_x][dt->p_y]);
	return (0);
}

void	put_imag(t_mlx *mlx, int x, int y)
{
	char	c;

	if (x >= getmap_hi(mlx->gm->dt->map) || \
		y >= (int)ft_strlen(mlx->gm->dt->map[x]))
		return ;
	c = mlx->gm->dt->map[x][y];
	if (c == '1')
		mlx->gm->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/wall.xpm", &mlx->gm->img_x, &mlx->gm->img_y);
	if (c == '0' || is_sep(c))
		mlx->gm->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/floor.xpm", &mlx->gm->img_x, &mlx->gm->img_y);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		mlx->gm->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/player.xpm", &mlx->gm->img_x, &mlx->gm->img_y);
	if (!mlx->gm->img)
		return ;
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, \
	mlx->gm->img, y * SIZE_H, x * SIZE_W);
	mlx_destroy_image(mlx->mlx_p, mlx->gm->img);
	mlx->gm->img = NULL;
}

void	drow_map(t_mlx *mlx, int key)
{
	int		x;
	int		y;

	x = 0;
	ft_mv(key, mlx->gm->dt);
	while (x < mlx->gm->map_h)
	{
		y = 0;
		mlx->gm->map_w = (int)ft_strlen(mlx->gm->dt->map[x]);
		while (y < mlx->gm->map_w)
		{
			put_imag(mlx, x, y);
			y++;
		}
		x++;
	}
}
