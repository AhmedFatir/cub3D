/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:29 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 18:38:40 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	if_surrounded(char *line)
{
	while (*line == 32 || (*line >= 9 && *line <= 13))
		line++;
	if (*line != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

int	if_validmap(char *line, int *flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != '1' && line[i] != 32 && line[i] != '0'
				&& line[i] != '\n') && !(line[i] == 'W' || line[i] == 'E'
				|| line[i] == 'N' || line[i] == 'S'))
			return (0);
		else if (line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'N' || line[i] == 'S')
			(*flag)++;
		i++;
	}
	return (1);
}

int	suroundedbyone(char **map)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (map[i])
	{
		if (!if_surrounded(map[i]) || !if_validmap(map[i], &flag) || flag > 1)
		{
			write(1, "Error\ninvalid map\n", 19);
			return (0);
		}
		i++;
	}
	if (flag == 0)
	{
		write(1, "Error\nMissing charachters of the map\n", 37);
		return (0);
	}
	return (1);
}

int	check_color_textures(char *line)
{
	while ((*line == ' ' || (*line >= 9 && *line <= 13)))
		line++;
	if ((!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2)
			|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2))
		|| (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
		return (1);
	return (0);
}

int	check_l_surroundedbyone(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != '1' && line[i] != 32)
			return (0);
	return (1);
}
