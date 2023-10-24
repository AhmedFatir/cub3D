/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
/*   Updated: 2023/10/24 20:51:02 by afatir           ###   ########.fr       */
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

typedef struct s_col
{
	char	**f;
	char	**c;
}t_col;

typedef struct s_data
{
	char	**map;
	char	*no;
	char	*we;
	char	*so;
	char	*ea;
	char	*f;
	char	*c;
	int		p_x;
	int		p_y;
	t_col	*col;
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
void	print_error(char *s, int *i);
void	init_n(t_info *n);
void	ft_free_data(t_data *dt, t_map *map, int *i);
void	check_extention(int ac, char **av);
void	fill_list(int ac, char **av, t_map **map);
//linked_list.c
void	free_list(t_map *list);
t_map	*cr_list(char *cmd);
void	add_end(t_map **a, t_map *n);
int		strlen_list(t_map **a);
char	*get_index_list(t_map *map, int index);
//parsing.c
char	**load_map(t_map *map, int *i, int j);
void	check_line(char *line, t_info *n, int j, int *i);
void	check_info(t_map *map, int *i);
char	*get_info(t_map *map, int *i, char *s);
t_data	*parsing(t_data *dt, int ac, char **av, t_map *map);
// pars_map.c
void	check_sides(char **map, int h, int *i);
void	check_first_last(char *line, int *i);
void	check_midle(char **map, int h, int *i, int j);
void	check_player(char **map, t_data *dt, int h, int *i);
char	**get_map(t_map *map, t_data *dt, int *i);
// pars_colors.c
void	check_colors(t_data *dt, int *i, char x, int count);
void	norme_colors(char *c, int *j, int *k);
void	alloc_color(t_col *col, char x, char *p);
int		check_color_numbers(char **p);
void	triming(t_data *dt, int *i, int j, char	*p);
//pars_utils.c
int		check_if_map(char *line);
int		getmap_hi(char **map);
int		check_if_full(char *map);
int		valide_symbols(char c);
void	check_midle_to(char *line, int k, int *i);
//pars_utils2.c
int		is_sep(char c);
void	check_directions(char *line, int *j, int *i, t_info *n);
#endif
