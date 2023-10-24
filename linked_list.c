/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:44:49 by afatir            #+#    #+#             */
/*   Updated: 2023/10/24 20:43:17 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_map *list)
{
	t_map	*tmp;
	t_map	*tmp1;

	if (list)
	{
		tmp = list;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			free(tmp->line);
			free(tmp);
			tmp = tmp1;
		}
	}
}

t_map	*cr_list(char *cmd)
{
	t_map		*s;
	static int	i;

	s = (t_map *)malloc(sizeof(t_map));
	if (!s)
		return (NULL);
	s->line = ft_strdup(cmd);
	s->index = ++i;
	s->next = NULL;
	free(cmd);
	return (s);
}

void	add_end(t_map **a, t_map *n)
{
	t_map	*tmp;

	tmp = *a;
	if (*a == NULL)
	{
		*a = n;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = n;
}

int	strlen_list(t_map **a)
{
	t_map	*tmp;
	int		ln;

	ln = 0;
	tmp = *a;
	while (tmp != NULL)
	{
		ln++;
		tmp = tmp->next;
	}
	return (ln);
}

char	*get_index_list(t_map *map, int index)
{
	while (map)
	{
		if (map->index == index)
			return (ft_strdup(map->line));
		map = map->next;
	}
	return (NULL);
}
