/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:09:51 by afatir            #+#    #+#             */
/*   Updated: 2023/10/23 21:52:58 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_sides(char **map, int h, int *i)
{
	int		j;
	int		k;

	j = 0;
	check_first_last(map[j], i);
	while (j < h)
	{
		k = 0;
		while (map[j][k] && (map[j][k] == 32 || map[j][k] == 9))
			k++;
		if (map[j][k] && map[j][k] != '1')
			*i = 1;
		if (ft_strlen(map[j]) > 2 && map[j][ft_strlen(map[j]) - 2] != '1')
			*i = 1;
		j++;
	}
	if (*i != 1)
		check_first_last(map[j - 1], i);
}

void	check_first_last(char *line, int *i)
{
	int		j;

	j = 0;
	if (line)
	{
		while (line[j] && (line[j] == 32 || line[j] == 9))
			j++;
		while (line[j])
		{
			if (line[j] != '1' && line[j] != 32 && line[j] != '\n')
				*i = 1;
			j++;
		}
		return ;
	}
	*i = 1;
}

void	check_midle(char **map, int h, int *i, int j)
{
	int		k;

	while (j < h)
	{
		k = 0;
		while (map[j][k])
		{
			if (map[j][k] == '0' || valide_symbols(map[j][k]) == 2)
			{
				if ((map[j][k - 1] && map[j][k - 1] == 32) || \
					(map[j][k + 1] && map[j][k + 1] == 32))
					*i = 1;
				if (map[j + 1])
					check_midle_to(map[j + 1], k, i);
				if (map[j - 1])
					check_midle_to(map[j - 1], k, i);
			}
			k++;
		}
		j++;
	}
}

void	check_player(char **map, t_data *dt, int h, int *i)
{
	int		j;
	int		k;
	int		count;

	j = 0;
	count = 0;
	while (j < h)
	{
		k = 0;
		while (map[j][k])
		{
			if (!valide_symbols(map[j][k]))
				*i = 1;
			if (valide_symbols(map[j][k]) == 2)
			{
				dt->p_x = j;
				dt->p_y = k;
				count++;
			}
			k++;
		}
		j++;
	}
	if (!count || count > 1)
		*i = 1;
}

char	**get_map(t_map *map, t_data *dt, int *i)
{
	char	**mp;
	int		h;

	ft_free_data(dt, map, i);
	mp = load_map(map, i, 0);
	print_error("Error\nerror loading the map\n", i);
	ft_free_data(dt, map, i);
	h = getmap_hi(mp);
	check_sides(mp, h, i);
	print_error("Error\nerror in the map sides\n", i);
	ft_free_data(dt, map, i);
	check_midle(mp, h, i, 0);
	print_error("Error\nerror inside the map\n", i);
	ft_free_data(dt, map, i);
	check_player(mp, dt, h, i);
	print_error("Error\ncaracter error\n", i);
	ft_free_data(dt, map, i);
	return (mp);
}
