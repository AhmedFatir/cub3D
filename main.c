/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by afatir            #+#    #+#             */
/*   Updated: 2023/12/01 17:45:09 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	v(void)
{
	system("leaks cub3D");
}

void printlist(t_txtr *head)
{
	t_txtr *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}
int	main(int ac, char **av)
{
	t_data	dt;
	atexit(v);
	if (!parsing(ac, av, &dt, dt.t))
		return (0);
	// free_map(&dt);
	// freelist(&dt.t);
	execution(&dt);
}
