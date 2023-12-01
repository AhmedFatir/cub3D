/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:41:00 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/01 04:39:10 by khbouych         ###   ########.fr       */
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
	(void)m;
	tmp = l_ture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "F", 1) || !ft_strncmp(tmp->key, "C", 1))
		{
			if (!ft_process_rgb_color(tmp, m))
			{
				write(1, "Error\ninvalid RGBA color\n", 26);
				exit(0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void get_rows_cols(t_data *m)
{
	int i;
	int j;

	i = 0;
	while (m->map2d[i])
	{
		j = 0;
		while (m->map2d[i][j])
			j++;
		if (j > m->cols)
			m->cols = j;
		i++;
	}
	m->rows = i;
}

int	parsing(int ac, char **av, t_data *m, t_txtr *l_ture)
{
	t_mlx	*smlx;
	int		count;

	smlx = ft_calloc(1 ,sizeof(t_mlx));
	l_ture = NULL;
	if (ac != 2 || !checkextension(av[1]))
	{
		write(1, "Error\ninvalid compilation\n", 27);
		exit(0);
	}
	count = 0;
	if (!read_map(av[1], m, &count))
		return (free(smlx), free(l_ture), 0);
	if (!valid_map(m))
		return (free_2d(m->sq_map), free_2d(m->map2d),
			free_2d(m->ture2d), free(l_ture), free(smlx), 0);
	if (!lst_ture(m, &l_ture))
		return (free(l_ture), 0);
	m->t = l_ture;
	if (!color_ture(m, l_ture))
		return (0);
	get_x_y_player(smlx,m);
	get_rows_cols(m);
	return (1);
}
