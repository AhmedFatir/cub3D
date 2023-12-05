/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:48:23 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/05 09:24:17 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ifvalid(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		&& (line[2] == 32 || (line[2] >= 9 && line[2] <= 13)))
		return (1);
	else if ((!ft_strncmp(line, "F", 1)
			|| !ft_strncmp(line, "C", 1))
		&& (line[1] == 32 || (line[1] >= 9 && line[1] <= 13)))
		return (1);
	return (0);
}

int	checktures_space_tab(char **ture2d, int count)
{
	int	i;

	i = -1;
	if (count != 6)
		return (0);
	while (++i < count)
	{
		if (!check_ifvalid(ture2d[i]))
		{
			write(1, "Error\ninvalid map element [texture/color]\n", 42);
			return (0);
		}
	}
	return (1);
}

int	check_pos_ofv(char *line)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (*line == ' ' || (*line >= 9 && *line <= 13)
		|| *line == 'C' || *line == 'F')
	{
		if (*line == 'C' || *line == 'F')
			flag++;
		line++;
	}
	if (flag != 1)
		return (0);
	if (!ft_isdigit(line[i]) || !ft_isdigit(line[(ft_strlen(line) - 1)]))
		return (0);
	while (line[i])
	{
		if ((!ft_isdigit(line[i]) && line[i] != ',')
			|| (line[i] == ',' && line[i + 1] && line[i + 1] == ','))
			return (0);
		i++;
	}
	return (1);
}

int	count_vergules(char *rgb)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (rgb[i])
		if (rgb[i++] == ',')
			count++;
	return (count);
}

int	parse_rgb(char **ture2d)
{
	int		i;
	char	*ptr;

	i = 0;
	while (ture2d[i])
	{
		ptr = ture2d[i];
		while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
			ptr++;
		if (ptr[0] == 'F' || ptr[0] == 'C')
		{
			if (count_vergules(ptr) != 2 || !check_pos_ofv(ptr))
			{
				write(1, "Error\ninvalid map element [texture/color]\n", 42);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
