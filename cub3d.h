/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
/*   Updated: 2023/10/21 20:36:58 by afatir           ###   ########.fr       */
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
	char			*line;
	int				index;
	struct s_map	*next;
}t_map;

typedef struct s_data
{
	char	**map;
	char	*no;
	char	*we;
	char	*so;
	char	*ea;
	char	*f;
	char	*c;
	int		mp_h;
	int		mp_w;

}t_data;

typedef struct s_info
{
	int		no;
	int		we;
	int		so;
	int		ea;
	int		f;
	int		c;
}t_info;

// fill_list.c
void	print_error(char *s);
void	print_msg(char *s, int fd, int i);
void	ft_free_data(t_data *dt);
void	check_extention(int ac, char **av);
void	fill_list(int ac, char **av, t_map **map);
//linked_list.c
void	free_list(t_map *list);
t_map	*cr_list(char *cmd);
void	add_end(t_map **a, t_map *n);
int		strlen_list(t_map **a);
char	*get_index_list(t_map *map, int index);
//parsing1_head.c
void	check_line(char *line, t_info *n, int j, int *i);
void	init_n(t_info *n);
void	check_info(t_map *map, int *i);
char	*get_info(t_map *map, int *i, char *s);
void	parsing(t_map *map, t_data *dt);
// parsing2_map.c
void	check_sides(char **map, int h, int *i);
char	**get_map(t_map *map, int *i);
//parsing3_utils.c
int		getmap_hi(char **map);
int		check_if_full(char *map);
char	**load_map(t_map *map, int *i);
#endif
