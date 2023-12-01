/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:38:41 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/01 20:25:02 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	checkcolorvalues(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
			return (free_2d(rgb), 0);
		i++;
	}
	return (free_2d(rgb), 1);
}

void	ft_process_rgb_color(t_txtr *tmp, t_data *m)
{
	if (!ft_strncmp(tmp->key, "F", 2))
	{
		m->ff = ft_split(tmp->value, ',');
		return ;
	}
	else if (!ft_strncmp(tmp->key, "C", 2))
	{
		m->cc = ft_split(tmp->value, ',');
		return ;
	}
}
