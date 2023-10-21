/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:49:36 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 17:01:56 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *s)
{
	static int	i;

	if (i == 0)
	{
		ft_putstr_fd(s, 2);
		i++;
	}
}

void	print_msg(char *s, int fd, int i)
{
	ft_putstr_fd(s, fd);
	exit(i);
}

void	ft_free_data(t_data *dt)
{
	if (dt->no)
		free(dt->no);
	if (dt->so)
		free(dt->so);
	if (dt->we)
		free(dt->we);
	if (dt->ea)
		free(dt->ea);
	if (dt->f)
		free(dt->f);
	if (dt->c)
		free(dt->c);
	ft_free_all(dt->map);
	free(dt);
	exit(1);
}

void	check_extention(int ac, char **av)
{
	int		i;

	if (ac != 2)
		print_msg("Error\nbad argument\n", 2, 1);
	i = ft_strlen(av[1]);
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' \
		|| av[1][i - 3] != 'c' || av[1][i - 4] != '.')
		print_msg("Error\nbad argument\n", 2, 1);
}

void	fill_list(int ac, char **av, t_map **map)
{
	int		fd;
	t_map	*ma;
	char	*p;

	check_extention(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		print_msg("Error\nerror opening file\n", 2, 1);
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
