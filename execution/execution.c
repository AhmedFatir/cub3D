/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/30 23:24:47 by afatir           ###   ########.fr       */
=======
/*   Updated: 2023/11/30 17:04:35 by khbouych         ###   ########.fr       */
>>>>>>> 9bfd40f3d26e871d79c461f4fb2723bc392e4e3c
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	ft_exit(t_mlx *mlx)
{
	mlx_delete_image(mlx->mlx_p, mlx->img);
	free_m(mlx);
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->tex);
	ft_putstr_fd("Game closed\n", 1);
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
	draw_map_tile2d(mlx);
	// draw_ray_2d(mlx, mlx->ray->ray_ngl, mlx->ray->distance, RED);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}
void	load_texture(t_tex *tex)
{

	// t_txtr *tmp;

	// tmp = l_ture;
	// while (tmp)
	// {
	// 	printf ("key = %s\n", tmp->key);
	// 	tmp = tmp->next;
	// }
	// exit(0);
	tex->ea = mlx_load_png("textures/ea.png");
	tex->no = mlx_load_png("textures/no.png");
	tex->so = mlx_load_png("textures/so.png");
	tex->we = mlx_load_png("textures/we.png");
}
void my_mouse(void *param)
{
	t_mlx *mlx;
	mlx = param;

	static int fix;

	if (fix++ == 0)
		mlx->ply->m_x = 500;
	mlx_get_mouse_pos(mlx->mlx_p, &mlx->ply->m_x, &mlx->ply->m_y);
	mlx->ply->angle += (float)(mlx->ply->m_x - 500)/ 500;
	mlx_set_mouse_pos(mlx->mlx_p, 500, 500);
}
void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	mlx.dt = dt;
	if (S_H > 1440 || S_W > 2560 || FOV > 180 || FOV < 0)
		exit(0);
	mlx.mlx_p = mlx_init(S_W, S_H, "cub3D", false);
	get_angle(&mlx);
	load_texture(mlx.tex);
	mlx_key_hook(mlx.mlx_p, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx_p, &drow_map_pixel, &mlx);
	mlx_set_cursor_mode(mlx.mlx_p, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(mlx.mlx_p, (void *)my_mouse, &mlx);
	mlx_loop(mlx.mlx_p);
	mlx_terminate(mlx.mlx_p);
	ft_exit(&mlx);
}