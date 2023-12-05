/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:16:33 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/05 14:16:56 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_x_y_player(t_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->sq_map[i])
	{
		j = 0;
		while (m->sq_map[i][j])
		{
			if (m->sq_map[i][j] == 'N' || m->sq_map[i][j] == 'S'
				|| m->sq_map[i][j] == 'W' || m->sq_map[i][j] == 'E')
			{
				m->p_x = j;
				m->p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	free_2d(char **m)
{
	int	i;

	i = 0;
	while (m[i])
		free(m[i++]);
	free(m);
}

int	checkextension(char *fname)
{
	char	*dotp;

	dotp = ft_strrchr(fname, '.');
	if (dotp && !ft_strcmp(dotp, ".cub"))
		return (1);
	else if (!fname || !dotp)
		return (0);
	return (0);
}

void	freelist(t_txtr **head)
{
	t_txtr	*tmp;

	tmp = *head;
	while (tmp)
	{
		*head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = *head;
	}
	free(*head);
}
