/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:38:41 by khbouych          #+#    #+#             */
/*   Updated: 2023/12/01 16:53:20 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	*ft_memcpy(void *dest, const void *src, unsigned int n)
// {
// 	unsigned int	i;
// 	char			*p_dest;
// 	char			*p_src;

// 	if (dest == NULL && src == NULL)
// 		return (0);
// 	p_dest = (char *)dest;
// 	p_src = (char *)src;
// 	i = -1;
// 	while (++i < n)
// 		p_dest[i] = p_src[i];
// 	return (p_dest);
// }

// char	*ft_strdup(char *s1)
// {
// 	char			*tmp;
// 	unsigned int	size;

// 	size = ft_strlen(s1);
// 	tmp = (char *)malloc(size + 1);
// 	if (!tmp)
// 		return (0);
// 	ft_memcpy(tmp, s1, size);
// 	tmp[size] = '\0';
// 	return (tmp);
// }

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
			return (free_2d(rgb),0);
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
