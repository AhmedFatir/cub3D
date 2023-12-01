/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:53:18 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/01 04:51:35 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_index(char *line, int i)
{
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

t_txtr	*new_texture(char *line)
{
	t_txtr	*list;

	list = (t_txtr *)malloc(sizeof(t_txtr));
	if (!list)
		return (NULL);
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			||!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
	{
		list->key = ft_substr(line, 0, 2);
		list->value = ft_substr(line, get_index(line, 2), ft_strlen(line));
	}
	else if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
	{
		list->key = ft_substr(line, 0, 1);
		list->value = ft_substr(line, get_index(line, 1), ft_strlen(line));
	}
	list->next = NULL;
	return (list);
}

t_txtr	*lst_back_ture(t_txtr *l_ture, t_txtr *new)
{
	t_txtr	*tmp;

	tmp = l_ture;
	if (l_ture == NULL)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (l_ture);
}

void	lst_back_ture2(t_txtr **l_ture, t_txtr *new)
{
	t_txtr	*tmp;

	tmp = *l_ture;
	if (*l_ture == NULL)
	{
		(*l_ture) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	lst_ture(t_data *m, t_txtr **l_ture)
{
	int		i;
	t_txtr	*tmp;

	i = 0;
	while (m->ture2d[i])
	{
		tmp = new_texture(m->ture2d[i++]);
		if (!tmp)
			return (0);
		lst_back_ture2(l_ture, tmp);
	}
	return (1);
}
