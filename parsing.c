/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:49:36 by afatir            #+#    #+#             */
/*   Updated: 2023/10/04 09:55:59 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_nodes(t_map *arg)
{
	t_map	*current;

	current = arg;
	while (current)
	{
		printf("%s", current->line);
		current = current->next;
	}
	// printf("\n\nlen->%d\n", ft_strlen_list(&arg));
}

void	fill_map(char *av, t_map **map)
{
	int		fd;
	t_map	*ma;
	char	*p;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nfile not exist\n");
		exit(1);
	}
	while (1)
	{
		p = get_next_line(fd);
		if (!p)
			break;
		ma = ft_cr_list(p);
		ft_add_end(map, ma);
	}
	close(fd);
}
void	ft_error(t_map *map)
{
	printf("Error\nmap error\n");	
	free_list(map);
	exit(1);
}
void	chack_first(t_map *map, char *f, char *s)
{
	int		i;

	i = 0;
	if (ft_strlen(f) < ft_strlen(s))
		ft_error(map);
	while (f[i])
	{
		if (f[i] != '1')
			ft_error(map);
		i++;
	}
	
}
// void	ft_checkc_midl(t_map *map, char *f, char *m, char *l)
// {
	
// }
void	check_map(t_map *map)
{
	t_map	*prev;
	t_map	*cur;
	t_map	*next;

	prev = map;
	cur = map;
	next = map;
	chack_first(map, cur->line, cur->next->line);
	while (cur)
	{
		cur = cur->next;
		// ft_checkc_midl(map, prev->line, cur->line);
	}
	
	
	
}
t_map	*parsing(t_map *map, int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nbad argument\n");
		exit(1);
    }
	fill_map(av[1], &map);
	print_nodes(map);
	// check_map(map);
	return (map);
}