/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:51:44 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 20:40:25 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**load_map(t_map *map, int *i)
{
	char	**mp;
	t_map	*tmp;
	int		j;

	tmp = map;
	j = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, "111", 3))
			break ;
		j++;
		tmp = tmp->next;
	}
	mp = ft_calloc(((strlen_list(&map) - j) + 1), sizeof(char *));
	j = 0;
	if (tmp)
	{
		while (tmp)
		{
			mp[j] = ft_strdup(tmp->line);
			tmp = tmp->next;
			j++;
		}
	}
	else
		*i = 1;
	return (mp);
}
