/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:51:44 by afatir            #+#    #+#             */
/*   Updated: 2023/10/23 20:57:21 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_map(char *line)
{
	int		i;

	i = 0;
	while (is_sep(line[i]))
		i++;
	if (line[i] && !ft_strncmp(&line[i], "1", 1))
		return (0);
	return (1);
}

int	getmap_hi(char **map)
{
	int		i;
	int		len;
	int		len1;

	i = 0;
	len = 0;
	len1 = 0;
	while (map[i])
	{
		if (!check_if_full(map[i]))
			len1++;
		else if (map[i] && check_if_full(map[i]))
		{
			len ++;
			len += len1;
			len1 = 0;
		}
		i++;
	}
	return (len);
}

int	check_if_full(char *map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i] != 32 && map[i] != 9 && map[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	valide_symbols(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	if (c == '1' || c == '0' || c == 32 || c == '\n' || c == 9)
		return (1);
	return (0);
}

void	check_midle_to(char *line, int k, int *i)
{
	int		len;

	len = (int)ft_strlen(line) - 1;
	if (k > len)
		*i = 1;
	else if (line[k] == '\n' || line[k] == 32 || line[k] == 9)
		*i = 1;
}
