/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
/*   Updated: 2023/10/04 08:02:26 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft_gcl_ptf/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# define SIZE 33

typedef struct s_map
{
   char	*line;
   int	index;
   struct s_map *next;
}t_map;

//parsing.c
t_map	*parsing(t_map *map, int ac, char **av);
//linked_list.c
void	free_list(t_map *list);
t_map	*ft_cr_list(char *cmd);
void	ft_add_end(t_map **a, t_map *n);
int		ft_strlen_list(t_map **a);

#endif
