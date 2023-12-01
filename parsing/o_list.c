/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:07:15 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/01 04:53:28 by khbouych         ###   ########.fr       */
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

static void	ft_skipp(int *i, const char *p_str, int *sign)
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

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;
	int			i;
	char		*p_str;
	long long	prev_res;

	p_str = (char *)str;
	i = 0;
	res = 0;
	sign = 1;
	ft_skipp(&i, &str[i], &sign);
	while (ft_isdigit(p_str[i]))
	{
		prev_res = res;
		res = res * 10 + p_str[i] - '0';
		if ((res / 10) != prev_res)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (sign * res);
}

int	valid_map(t_data *m)
{
	int	i;
	int	maxlen;

	maxlen = getsize_largline(m->map2d);
	i = 0;
	m->sq_map = malloc(sizeof(char *) * (getsizemap(m->map2d) + 1));
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
		return (0);
	return (1);
}
