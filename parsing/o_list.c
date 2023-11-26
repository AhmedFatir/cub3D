/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:07:15 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 18:54:26 by afatir           ###   ########.fr       */
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

// char	*ft_strrchr(char *str, int c)
// {
// 	int	i;

// 	i = ft_strlen(str);
// 	while (i >= 0)
// 	{
// 		if (str[i] == (char)c)
// 			return ((char *)&str[i]);
// 		i--;
// 	}
// 	return (0);
// }
