/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:09:51 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 21:07:02 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_sides(char **map, int h, int *i)
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
		if (ft_strlen(map[j]) > 2 && map[j][ft_strlen(map[j]) - 2] != '1')
		{
			print_error("Error\nin right wall\n");
			*i = 1;
		}
		j++;
	}
}

void	check_first_last(char *line, int *i)
{
	int		j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '1' && line[j] != 32 && line[j] != '\n')
			*i = 1;
		j++;
	}
}

void	check_midle(char **map, int h, int *i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	check_first_last(map[j], i);
	while (j < h)
	{
		//check_ midll;
		j++;
	}
	check_first_last(map[j - 1], i);
}

char	**get_map(t_map *map, int *i)
{
	char	**mp;
	int		h;

	mp = load_map(map, i);
	if (*i == 1)
		print_error("Error\nno map in the file\n");
	h = getmap_hi(mp);
	check_sides(mp, h, i);
	check_midle(mp, h, i);
	if (*i == 1)
		print_error("Error\nmap not surrounded by walls\n");
	return (mp);
}
