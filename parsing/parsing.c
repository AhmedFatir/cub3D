/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:41:00 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/05 17:21:47 by afatir           ###   ########.fr       */
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

	m->cc = NULL;
	m->ff = NULL;
	tmp = l_ture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "F", 1) || !ft_strncmp(tmp->key, "C", 1))
		{
			if (!checkcolorvalues(ft_split(tmp->value, ',')))
			{
				write(1, "Error\ninvalid RGBA color\n", 26);
				return (0);
			}
			ft_process_rgb_color(tmp, m);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	free_map(t_data *m)
{
	free_2d(m->sq_map);
	free_2d(m->map2d);
	free_2d(m->ture2d);
	if (m->ff)
		free_2d(m->ff);
	if (m->cc)
		free_2d(m->cc);
}

void	get_rows_cols(t_data *m)
{
	int	i;
	int	j;

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
	int		count;

	l_ture = NULL;
	if (ac != 2 || !checkextension(av[1]))
	{
		write(1, "Error\ninvalid compilation\n", 26);
		exit(0);
	}
	count = 0;
	if (!read_map(av[1], m, &count))
		return (0);
	if (!valid_map(m))
		return (0);
	if (!lst_ture(m, &l_ture))
		return (free_map(m), freelist(&l_ture), 0);
	if (!color_ture(m, l_ture))
		return (free_map(m), freelist(&l_ture), 0);
	get_x_y_player(m);
	get_rows_cols(m);
	m->t = l_ture;
	return (1);
}
