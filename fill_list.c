/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:49:36 by afatir            #+#    #+#             */
/*   Updated: 2023/10/24 20:34:18 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *s, int *i)
{
	static int	j;

	if (!j && *i)
	{
		ft_putstr_fd(s, 2);
		j++;
	}
}

void	init_n(t_info *n)
{
	n->no = 0;
	n->we = 0;
	n->so = 0;
	n->ea = 0;
	n->f = 0;
	n->c = 0;
}

void	ft_free_data(t_data *dt, t_map *map, int *i)
{
	if (!*i)
		return ;
	free(dt->no);
	free(dt->so);
	free(dt->we);
	free(dt->ea);
	free(dt->f);
	free(dt->c);
	ft_free_all(dt->map);
	ft_free_all(dt->col->c);
	ft_free_all(dt->col->f);
	free(dt->col);
	free(dt);
	free_list(map);
	exit(1);
}

void	check_extention(int ac, char **av)
{
	int		i;

	if (ac != 2)
	{
		print_error("Error\nbad argument\n", &ac);
		exit(1);
	}
	i = ft_strlen(av[1]);
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' \
		|| av[1][i - 3] != 'c' || av[1][i - 4] != '.')
	{
		print_error("Error\nbad argument\n", &ac);
		exit(1);
	}
}

void	fill_list(int ac, char **av, t_map **map)
{
	int		fd;
	t_map	*ma;
	char	*p;

	check_extention(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		print_error("Error\nerror opening file\n", &ac);
		exit(1);
	}
	while (1)
	{
		p = get_next_line(fd);
		if (!p)
			break ;
		ma = cr_list(p);
		add_end(map, ma);
	}
	close(fd);
}
