/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/10/04 09:05:37 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void exetuting(t_map **map)
{
	(void)map;
	return; 
}

void v()
{
	system("leaks cub3D");
}
int main(int ac, char **av)
{   
	// atexit(v);
	t_map	*map;

	map = NULL;
	map = parsing(map, ac, av);
	exetuting(&map);
	free_list(map);
	return (0);
}