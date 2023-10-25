/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/10/25 14:13:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	v(void)
{
	system("leaks cub3D");
}

void	print_data(t_data *dt)
{
	int		i;

	i = 0;
	while (dt->map[i])
		ft_printf("|%s|\n", dt->map[i++]);
	i = 0;
	while (dt->col->f[i])
		ft_printf("%s ", dt->col->f[i++]);
	i = 0;
	while (dt->col->c[i])
		ft_printf("%s ", dt->col->c[i++]);
	i = 1;
	ft_free_data(dt, NULL, &i, 1);
}

int	main(int ac, char **av)
{
	t_data	*dt;

	atexit(v);
	dt = parsing(NULL, ac, av, NULL);
	execution(dt, NULL);
	print_data(dt);
	return (0);
}
