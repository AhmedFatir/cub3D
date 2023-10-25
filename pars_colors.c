/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:04:07 by afatir            #+#    #+#             */
/*   Updated: 2023/10/25 10:55:38 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_colors(t_data *dt, int *i, char x, int count)
{
	int		j;
	int		k;
	char	*c;
	char	*p;

	j = 0;
	c = dt->f;
	if (x == 'c')
		c = dt->c;
	norme_colors(c, &j, &k);
	while (c[j])
	{
		if ((!ft_isdigit(c[j]) && c[j] != ',' && c[j] != '\n' \
			&& !is_sep(c[j])) || count > 2)
		{
			*i = 1;
			print_error("Error\nerror in colors\n", i);
		}
		if (c[j] == ',')
			count++;
		j++;
	}
	p = ft_substr(c, k, k - j);
	alloc_color(dt->col, x, p);
}

void	norme_colors(char *c, int *j, int *k)
{
	while (c[*j] && is_sep(c[*j]))
		(*j)++;
	*j = *j + 2;
	*k = *j;
	while (c[*j] && is_sep(c[*j]))
		(*j)++;
}

void	alloc_color(t_col *col, char x, char *p)
{
	if (x == 'c')
		col->c = ft_split(p, ',');
	else
		col->f = ft_split(p, ',');
	free(p);
}

int	check_color_numbers(char **p)
{
	int		i;

	i = 0;
	while (p[i])
	{
		if (ft_atoi(p[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}

void	triming(t_data *dt, int *i, int j, char	*p)
{
	while (dt->col->c[++j])
	{
		p = ft_strtrim(dt->col->c[j], " \t");
		free(dt->col->c[j]);
		dt->col->c[j] = ft_strdup(p);
		free(p);
	}
	if (j > 3 || !check_color_numbers(dt->col->c))
	{
		*i = 1;
		print_error("Error\nerror in colors\n", i);
	}
	j = -1;
	while (dt->col->f[++j])
	{
		p = ft_strtrim(dt->col->f[j], " \t");
		free(dt->col->f[j]);
		dt->col->f[j] = ft_strdup(p);
		free(p);
	}
	if (j > 3 || !check_color_numbers(dt->col->f))
	{
		*i = 1;
		print_error("Error\nerror in colors\n", i);
	}
}
