/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 16:58:57 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	v(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*dt;
	// atexit(v);
	map = NULL;
	dt = (t_data *)malloc(sizeof(t_data));
	fill_list(ac, av, &map);
	parsing(map, dt);
	return (0);
}
