/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 05:18:21 by afatir            #+#    #+#             */
/*   Updated: 2023/07/10 10:35:41 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->g_x * SIZE, \
	data->g_y * SIZE, "cub3D");
	ft_print_map(data);
	mlx_hook(data->mlx_win, 2, 0, ft_hook, data);
	mlx_hook(data->mlx_win, 17, 0, ft_ecs, data);
	mlx_loop(data->mlx);
}

void	p_position(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->g_y)
	{
		j = 0;
		while (j < data->g_x)
		{
			if (data->map[i][j] == 'P')
			{
				data->x = j;
				data->y = i;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_map(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->g_y)
	{
		x = 0;
		while (x < data->g_x)
		{
			print_image(data, x, y);
			x++;
		}
		y++;
	}
}

void	print_image(t_data *data, int x, int y)
{
	if (x >= data->g_x || y >= data->g_y)
		return ;
	if (data->map[y][x] == 'C')
		data->image = mlx_xpm_file_to_image(data->mlx, \
		"pirites/collectibles.xpm", &data->img_x, &data->img_y);
	if (data->map[y][x] == 'E')
		data->image = mlx_xpm_file_to_image(data->mlx, \
		"pirites/opened_gate.xpm", &data->img_x, &data->img_y);
	if (data->map[y][x] == 'P')
		data->image = mlx_xpm_file_to_image(data->mlx, \
		"pirites/player.xpm", &data->img_x, &data->img_y);
	if (data->map[y][x] == '0')
		data->image = mlx_xpm_file_to_image(data->mlx, \
		"pirites/floor.xpm", &data->img_x, &data->img_y);
	if (data->map[y][x] == '1')
		data->image = mlx_xpm_file_to_image(data->mlx, \
		"pirites/wall.xpm", &data->img_x, &data->img_y);
	check(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->image, x * SIZE, y * SIZE);
	mlx_destroy_image(data->mlx, data->image);
	data->image = NULL;
}
