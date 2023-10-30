/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:23:36 by afatir            #+#    #+#             */
/*   Updated: 2023/10/30 11:11:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_sep(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

void	check_directions(char *line, int *j, int *i, t_info *n)
{
	if (line[*j] == 'N' && line[*j + 1] == 'O' && is_sep(line[*j + 2]))
		n->no++;
	else if (line[*j] == 'S' && line[*j + 1] == 'O' && is_sep(line[*j + 2]))
		n->so++;
	else if (line[*j] == 'W' && line[*j + 1] == 'E' && is_sep(line[*j + 2]))
		n->we++;
	else if (line[*j] == 'E' && line[*j + 1] == 'A' && is_sep(line[*j + 2]))
		n->ea++;
	else if (line[*j] == 'F' && is_sep(line[*j + 1]))
		n->f++;
	else if (line[*j] == 'C' && is_sep(line[*j + 1]))
		n->c++;
	else
		*i = 1;
}

char	*ft_strtrim_back(char *s1, char *set)
{
	int		end;

	if (!s1 || !set)
		return (0);
	end = ft_strlen(s1) - 1;
	while (end > 0 && *s1 && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, 0, end + 1));
}

void	get_h_w(t_game *mlx)
{
	int		i;

	i = 0; 
	mlx->map_h = getmap_hi(mlx->dt->map);
	mlx->map_w = 0;
	while (i < mlx->map_h)
	{
		if ((int)ft_strlen(mlx->dt->map[i]) > mlx->map_w)
			mlx->map_w = (int)ft_strlen(mlx->dt->map[i]);
		i++;
	}
}