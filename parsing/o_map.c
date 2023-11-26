/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:02:09 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 18:54:41 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	getsize_largline(char **map)
{
	int	i;
	int	max;

	i = -1;
	max = ft_strlen(map[0]);
	while (map[++i])
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
	return (max);
}

int	getsizemap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	*fixline(char *line, int maxlen)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (maxlen + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (i < maxlen)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	h_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					write(1, "Error\ninvalid map (h)\n", 23);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	v_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
				{
					write(1, "Error\ninvalid map (v)\n", 23);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
