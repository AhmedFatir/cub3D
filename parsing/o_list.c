/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:07:15 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/05 13:58:53 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*removespaces(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	while (*src)
	{
		if (*src != '\t' && *src != '\r')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	return (str);
}

int	check_duplicat(t_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->ture2d[i])
	{
		j = i + 1;
		while (m->ture2d[j])
		{
			if (!ft_strncmp(m->ture2d[i], m->ture2d[j], 2))
			{
				write(1, "Error\nDuplicate map element [texture/color]\n", 45);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_skipp(int *i, const char *p_str, int *sign)
{
	while ((p_str[*i] >= 9 && p_str[*i] <= 13) || p_str[*i] == ' ')
		(*i)++;
	if (p_str[*i] == '-' || p_str[*i] == '+')
	{
		if (p_str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	valid_map(t_data *m)
{
	int	i;
	int	maxlen;

	maxlen = getsize_largline(m->map2d);
	i = 0;
	m->sq_map = ft_calloc(sizeof(char *), (getsizemap(m->map2d) + 1));
	if (!m->sq_map)
		return (0);
	while (m->map2d[i])
	{
		if (maxlen == (int)ft_strlen(m->map2d[i]))
			m->sq_map[i] = ft_strdup(m->map2d[i]);
		else
			m->sq_map[i] = fixline(m->map2d[i], maxlen);
		i++;
	}
	m->sq_map[i] = NULL;
	m->h_map = getsizemap(m->sq_map);
	m->w_map = ft_strlen(m->sq_map[0]);
	if (!h_map(m->sq_map) || !v_map(m->sq_map))
		return (free_2d(m->sq_map), free_2d(m->map2d), free_2d(m->ture2d), 0);
	return (1);
}
