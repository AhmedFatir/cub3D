/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:09:51 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 17:03:13 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_left(char **map, int h, int *i)
{
	int		j;

	j = 0;
	while (j < h)
	{
		if (map[j][0] != '1')
		{
			print_error("Error\nin left wall\n");
			*i = 1;
		}
		j++;
	}
}

void	check_right(char **map, int h, int *i)
{
	int		j;

	j = 0;
	while (j < h)
	{
		if (ft_strlen(map[j]) > 2 && map[j][ft_strlen(map[j]) - 2] != '1')
		{
			print_error("Error\nin right wall\n");
			*i = 1;
		}
		j++;
	}
}

char	**get_map(t_map *map, int *i)
{
	char	**mp;
	int		h;

	mp = load_map(map);
	h = getmap_hi(mp);
	check_left(mp, h, i);
	check_right(mp, h, i);
	// check_midle(mp, h, i);
	return (mp);
}
