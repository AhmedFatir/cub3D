/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/23 01:22:47 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_mlx *mlx)
{
	int		i;

	i = 1;
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	ft_free_data(mlx->dt, NULL, &i, 0);
	free(mlx->ply);
	free(mlx->ray);
	print_error("Game closed\n", &i);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0)
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0)
		return ;
	else if (y >= S_H)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(int *)dst = color;
}

void	get_tex(t_mlx *mlx)
{
	mlx->tex_no.img = mlx_xpm_file_to_image(mlx->mlx_p, \
	mlx->dt->no, &mlx->tex_no.width, &mlx->tex_no.height);
	mlx->tex_so.img = mlx_xpm_file_to_image(mlx->mlx_p, \
	mlx->dt->so, &mlx->tex_so.width, &mlx->tex_so.height);
	mlx->tex_ea.img = mlx_xpm_file_to_image(mlx->mlx_p, \
	mlx->dt->ea, &mlx->tex_ea.width, &mlx->tex_ea.height);
	mlx->tex_we.img = mlx_xpm_file_to_image(mlx->mlx_p, \
	mlx->dt->we, &mlx->tex_we.width, &mlx->tex_we.height);
	if (!mlx->tex_we.img || !mlx->tex_ea.img || \
	!mlx->tex_so.img || !mlx->tex_no.img)
		ft_exit(mlx);
	mlx->tex_no.addr = (int *)mlx_get_data_addr(mlx->tex_no.img, \
	&mlx->tex_no.bpp, &mlx->tex_no.line_len, &mlx->tex_no.endi);
	mlx->tex_so.addr = (int *)mlx_get_data_addr(mlx->tex_so.img, \
	&mlx->tex_so.bpp, &mlx->tex_so.line_len, &mlx->tex_so.endi);
	mlx->tex_ea.addr = (int *)mlx_get_data_addr(mlx->tex_ea.img, \
	&mlx->tex_ea.bpp, &mlx->tex_ea.line_len, &mlx->tex_ea.endi);
	mlx->tex_we.addr = (int *)mlx_get_data_addr(mlx->tex_we.img, \
	&mlx->tex_we.bpp, &mlx->tex_we.line_len, &mlx->tex_we.endi);
}

int	drow_map_pixel(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_p, mlx->win);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, \
		&mlx->line_len, &mlx->endi);
	cub_hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img, 0, 0);
	return (0);
}

void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.dt = dt;
	get_h_w(&mlx);
	mlx.mlx_p = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_p, S_W, S_H, "cub3D");
	get_tex(&mlx);
	get_angle(&mlx);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_press, &mlx);
	mlx_hook(mlx.win, 3, 0, ft_release, &mlx);
	mlx_loop_hook(mlx.mlx_p, drow_map_pixel, &mlx);
	mlx_loop(mlx.mlx_p);
}
