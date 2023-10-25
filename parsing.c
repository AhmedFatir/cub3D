/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:10:04 by afatir            #+#    #+#             */
/*   Updated: 2023/10/25 14:15:43 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**load_map(t_map *map, int *i, int j)
{
	char	**mp;
	t_map	*tmp;

	tmp = map;
	while (tmp)
	{
		if (!check_if_map(tmp->line))
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
			mp[j] = ft_strtrim_back(tmp->line, "\n \t");
			tmp = tmp->next;
			j++;
		}
	}
	else
		*i = 1;
	return (mp);
}

void	check_line(char *line, t_info *n, int j, int *i)
{
	while (line[j])
	{
		while (line[j] && (line[j] == 32 || line[j] == 9))
			j++;
		if (line[j] && line[j + 1] && line[j + 2])
		{
			check_directions(line, &j, i, n);
			return ;
		}
		j++;
	}
}

void	check_info(t_map *map, int *i)
{
	t_map	*mp;
	t_info	n;
	int		j;

	init_n(&n);
	j = 0;
	mp = map;
	while (mp)
	{
		if (!check_if_map(mp->line))
			break ;
		check_line(mp->line, &n, 0, i);
		mp = mp->next;
	}
	if (n.no > 1 || n.so > 1 || n.we > 1 || n.ea > 1 || n.c > 1 || n.f > 1)
		*i = 1;
	if (n.no == 0 || n.so == 0 || n.we == 0 || n.ea == 0 \
		|| n.c == 0 || n.f == 0)
		*i = 1;
}

char	*get_info(t_map *map, int *i, char *s)
{
	t_map	*mp;
	int		j;

	j = 0;
	mp = map;
	while (mp && ft_strncmp(mp->line, "1", 1))
	{
		j = 0;
		while (mp->line[j])
		{
			while (mp->line[j] == 32 || mp->line[j] == 9 || mp->line[j] == '\n')
				j++;
			if (!ft_strncmp(s, &mp->line[j], 2))
				return (ft_strdup(mp->line));
			else
				break ;
		}
		mp = mp->next;
	}
	*i = 1;
	return (NULL);
}

t_data	*parsing(t_data *dt, int ac, char **av, t_map *map)
{
	int		i;

	i = 0;
	fill_list(ac, av, &map);
	dt = (t_data *)ft_calloc(sizeof(t_data), 1);
	dt->col = (t_col *)ft_calloc(sizeof(t_col), 1);
	check_info(map, &i);
	print_error("Error\nwrong file format\n", &i);
	dt->no = get_info(map, &i, "NO");
	dt->so = get_info(map, &i, "SO");
	dt->we = get_info(map, &i, "WE");
	dt->ea = get_info(map, &i, "EA");
	dt->f = get_info(map, &i, "F ");
	dt->c = get_info(map, &i, "C ");
	ft_free_data(dt, map, &i, 1);
	check_colors(dt, &i, 'c', 0);
	check_colors(dt, &i, 'f', 0);
	triming(dt, &i, -1, NULL);
	dt->map = get_map(map, dt, &i);
	free_list(map);
	return (dt);
}
