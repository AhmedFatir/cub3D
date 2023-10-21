/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:51:44 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 17:02:30 by afatir           ###   ########.fr       */
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

char	**load_map(t_map *map)
{
	char	**mp;
	t_map	*tmp;
	int		i;

	tmp = map;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, "111", 3))
			break ;
		i++;
		tmp = tmp->next;
	}
	mp = ft_calloc(((strlen_list(&map) - i) + 1), sizeof(char *));
	i = 0;
	if (tmp)
	{
		while (tmp)
		{
			mp[i] = ft_strdup(tmp->line);
			tmp = tmp->next;
			i++;
		}
	}
	return (mp);
}
