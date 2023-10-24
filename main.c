/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/10/24 20:50:51 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_data(t_data *dt)
{
	int		i;

	i = 0;
	while (dt->map[i])
		ft_printf("%s", dt->map[i++]);
	ft_printf("\n");
	i = 0;
	while (dt->col->c[i])
		ft_printf("%s ", dt->col->c[i++]);
	i = 0;
	while (dt->col->f[i])
		ft_printf("%s ", dt->col->f[i++]);
	i = 1;
	ft_free_data(dt, NULL, &i);
}

void	v(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	*dt;
	t_map	*map;

	atexit(v);
	dt = NULL;
	map = NULL;
	dt = parsing(dt, ac, av, map);
	print_data(dt);
	return (0);
}
