/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:41:00 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/30 16:58:46 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_m(t_mlx *mlx)
{
	if (mlx->dt->sq_map)
		free_2d(mlx->dt->sq_map);
	if (mlx->dt->map2d)
		free_2d(mlx->dt->map2d);
	if (mlx->dt->ture2d)
		free_2d(mlx->dt->ture2d);
	if (mlx->dt->ff)
		free_2d(mlx->dt->ff);
	if (mlx->dt->cc)
		free_2d(mlx->dt->cc);
}

int	color_ture(t_data *m, t_txtr *l_ture)
{
	t_txtr	*tmp;
	tmp = l_ture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "F", 2) || !ft_strncmp(tmp->key, "C", 2))
		{
			if (!ft_process_rgb_color(tmp, m))
			{
				write(1, "Error\ninvalid RGBA color\n", 26);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	parsing(int ac, char **av, t_data *m, t_txtr *l_ture)
{
	t_mlx	*smlx;
	int		count;

	smlx = ft_calloc(1 ,sizeof(t_mlx));
	l_ture = NULL;
	if (ac != 2 || !checkextension(av[1]))
		return (free(smlx), free(l_ture),
			write(1, "Error\ninvalid args\n", 20), 0);
	count = 0;
	if (!read_map(av[1], m, &count))
		return (free(smlx), free(l_ture), 0);
	if (!valid_map(m))
		return (free_2d(m->sq_map), free_2d(m->map2d),
			free_2d(m->ture2d), free(l_ture), free(smlx), 0);
	if (!lst_ture(m, &l_ture))
		return (free(l_ture), 0);
	if (!color_ture(m, l_ture))
		return (free_m(smlx), freelist(&l_ture), free(smlx), 0);
	get_x_y_player(smlx,m);
	return (1);
}
