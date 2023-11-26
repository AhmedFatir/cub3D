/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/11/26 19:41:08 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	v(void)
{
	system("leaks cub3D");
}
// void	set_default(t_data *dt)
// {
// 	dt->map2d = ft_calloc(6, sizeof(char *));
// 	dt->map2d[0] = ft_strdup("11111111111111111111111111");
// 	dt->map2d[1] = ft_strdup("11000000001100000000000011");
// 	dt->map2d[2] = ft_strdup("1011000001110S000000000011");
// 	dt->map2d[3] = ft_strdup("10010000000000000000000011");
// 	dt->map2d[4] = ft_strdup("11111111 1111111 111111111");
// 	dt->no = ft_strdup("textures/no.xpm");
// 	dt->we = ft_strdup("textures/we.xpm");
// 	dt->so = ft_strdup("textures/so.xpm");
// 	dt->ea = ft_strdup("textures/ea.xpm");
// 	dt->f = ft_strdup("220,100,0");
// 	dt->c = ft_strdup("225,30,0");	
// 	dt->p_x = 14;
// 	dt->p_y = 3;
// 	dt->map_h = 5;
// 	dt->map_w = 26;
// }
int	main(int ac, char **av)
{
	atexit(v);
	// set_default(&dt);
	t_txtr *l_ture = NULL;
	t_data dt;
	if (!parsing(ac, av, &dt, l_ture))
		return (0);
	int i = 0;
	while (dt.map2d[i])
		ft_printf("%s\n", dt.map2d[i++]);
	
	execution(&dt);
	return (0);
}
