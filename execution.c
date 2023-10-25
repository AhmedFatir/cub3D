/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/10/25 14:20:37 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_game *mlx)
{
	int	i;

	i = 1;
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	print_error("Game closed\n", &i);
	ft_free_data(mlx->dt, NULL, &i, 0);
	free(mlx);
	exit(0);
	return (0);
}

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
	if ((key == 0) && (dt->map[dt->p_x][dt->p_y - 1] == '0'))
		mv_left_and_right(dt, 1, dt->map[dt->p_x][dt->p_y]);
	else if ((key == 2) && (dt->map[dt->p_x][dt->p_y + 1] == '0'))
		mv_left_and_right(dt, 2, dt->map[dt->p_x][dt->p_y]);
	else if ((key == 1) && (dt->map[dt->p_x + 1][dt->p_y] == '0'))
		mv_down_and_up(dt, 1, dt->map[dt->p_x][dt->p_y]);
	else if ((key == 13) && (dt->map[dt->p_x - 1][dt->p_y] == '0'))
		mv_down_and_up(dt, 2, dt->map[dt->p_x][dt->p_y]);
	return (0);
}

void	put_imag(t_game *mlx, int x, int y)
{
	char	c;

	if (x >= getmap_hi(mlx->dt->map) || y >= (int)ft_strlen(mlx->dt->map[x]))
		return ;
	c = mlx->dt->map[x][y];
	if (c == '1')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/wall.xpm", &mlx->img_x, &mlx->img_y);
	if (c == '0' || is_sep(c))
		mlx->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/floor.xpm", &mlx->img_x, &mlx->img_y);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx_p, \
		"textures/player.xpm", &mlx->img_x, &mlx->img_y);
	if (!mlx->img)
		return ;
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, \
	mlx->img, y * SIZE_H, x * SIZE_W);
	mlx_destroy_image(mlx->mlx_p, mlx->img);
	mlx->img = NULL;
}

void	drow_map(t_game *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x < mlx->map_h)
	{
		y = 0;
		mlx->map_w = (int)ft_strlen(mlx->dt->map[x]);
		while (y < mlx->map_w)
		{
			put_imag(mlx, x, y);
			y++;
		}
		x++;
	}
}

int	ft_hook(int key, t_game *mlx)
{
	if (key == 53)
		ft_exit(mlx);
	else
		ft_mv(key, mlx->dt);
	drow_map(mlx);
	return (0);
}

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

void	execution(t_data *dt, t_game *mlx)
{
	mlx = (t_game *)ft_calloc(sizeof(t_game), 1);
	mlx->dt = dt;
	mlx->mlx_p = mlx_init();
	get_h_w(mlx);
	mlx->win = mlx_new_window(mlx->mlx_p, \
	(mlx->map_w * SIZE_H), (mlx->map_h * SIZE_W), "cub3D");
	drow_map(mlx);
	mlx_hook(mlx->win, 17, 0, ft_exit, mlx);
	mlx_hook(mlx->win, 2, 0, ft_hook, mlx);
	mlx_loop(mlx->mlx_p);
}
