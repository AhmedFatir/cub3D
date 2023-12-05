/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:43:09 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/05 14:14:29 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*getmap(t_data *m)
{
	m->map = ft_strdup("");
	while (m->line)
	{
		if (m->line[0] == '\n')
		{
			write(1, "Error\nempty ligne in the map\n", 29);
			return (freeme(m->map, m->line, -1), NULL);
		}
		m->map = ft_strjoin(m->map, m->line);
		free(m->line);
		m->line = get_next_line(m->fd);
	}
	return (m->map);
}

int	read_map_(t_data *m, int count)
{
	m->map = getmap(m);
	if (!m->map)
		return (0);
	m->map2d = ft_split(m->map, '\n');
	if (!m->map2d)
	{
		free(m->map);
		return (0);
	}
	free(m->map);
	if (!checktures_space_tab(m->ture2d, count)
		|| !parse_rgb(m->ture2d) || !check_duplicat(m)
		|| !check_first_last_line(m->map2d) || !suroundedbyone(m->map2d))
	{
		free_2d(m->map2d);
		return (0);
	}
	return (1);
}

void	freeme(char *ture, char *line, int fd)
{
	if (ture)
		free(ture);
	if (line)
		free(line);
	if (fd > 0)
		close (fd);
}

int	read_map(char *av, t_data *m, int *count)
{
	m->fd = open(av, O_RDONLY);
	if (m->fd == -1)
		return (write(1, "Error\ninvalid file\n", 20), 0);
	m->line = get_next_line(m->fd);
	if (m->line == NULL)
		return (write(1, "Error\nempty file\n", 18), 0);
	m->ture = ft_strdup("");
	while (m->line && m->line[0] != '1' && m->line[0] != 32)
	{
		if (check_color_textures(m->line))
		{
			m->ture = ft_strjoin(m->ture, m->line);
			(*count)++;
		}
		free(m->line);
		m->line = get_next_line(m->fd);
	}
	if (!check_countture(m, *count))
		return (freeme(NULL, NULL, m->fd), 0);
	m->ture2d = ft_split(m->ture, '\n');
	if (!m->ture2d)
		return (freeme(m->ture, NULL, m->fd), 0);
	if (!read_map_(m, *count))
		return (freeme(m->ture, NULL, m->fd), free_2d(m->ture2d), 0);
	return (freeme(m->ture, m->line, m->fd), 1);
}
