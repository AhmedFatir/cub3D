/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:10:04 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 16:55:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_line(char *line, t_info *n, int j)
{
	while (line[j])
	{
		while (line[j] && (line[j] == 32 || line[j] == 9))
			j++;
		if (line[j] && line[j + 1])
		{
			if (line[j] == 'N' && line[j + 1] == 'O')
				n->no++;
			else if (line[j] == 'S' && line[j + 1] == 'O')
				n->so++;
			else if (line[j] == 'W' && line[j + 1] == 'E')
				n->we++;
			else if (line[j] == 'E' && line[j + 1] == 'A')
				n->ea++;
			else if (line[j] == 'F' && (line[j + 1] == 32 || line[j + 1] == 9))
				n->f++;
			else if (line[j] == 'C' && (line[j + 1] == 32 || line[j + 1] == 9))
				n->c++;
			else
				n->no = 20;
			return ;
		}
		j++;
	}
}

void	init_n(t_info *n)
{
	n->no = 0;
	n->we = 0;
	n->so = 0;
	n->ea = 0;
	n->f = 0;
	n->c = 0;
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
		if (!ft_strncmp(mp->line, "111", 3))
			break ;
		check_line(mp->line, &n, 0);
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
	(void)s;
	while (mp && ft_strncmp(mp->line, "111", 3))
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

void	parsing(t_map *map, t_data *dt)
{
	int		i;

	i = 0;
	check_info(map, &i);
	dt->no = get_info(map, &i, "NO");
	dt->so = get_info(map, &i, "SO");
	dt->we = get_info(map, &i, "WE");
	dt->ea = get_info(map, &i, "EA");
	dt->f = get_info(map, &i, "F ");
	dt->c = get_info(map, &i, "C ");
	dt->map = get_map(map, &i);
	if (i == 1)
		ft_free_data(dt);
	free_list(map);
}
