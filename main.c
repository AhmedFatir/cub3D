/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/30 20:39:19 by afatir           ###   ########.fr       */
=======
/*   Updated: 2023/11/30 16:54:45 by khbouych         ###   ########.fr       */
>>>>>>> 9bfd40f3d26e871d79c461f4fb2723bc392e4e3c
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	v(void)
{
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	t_data	dt;
	// atexit(v);
	if (!parsing(ac, av, &dt, NULL))
		return (0);
	execution(&dt);
	return (0);
}
