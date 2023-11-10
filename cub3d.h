/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
/*   Updated: 2023/11/10 19:44:06 by afatir           ###   ########.fr       */
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
# include <math.h>

# define SIZE_H 48
# define SIZE_W 48

# define FOV 60
# define NUM_RAYS 200
# define PLAYER_SPEED (TILE_SIZE * 0.1f)
# define RAY_STEP 0.1
# define TILE_SIZE SIZE_H
# define ROTATION_SPEED (M_PI / 90)
# define MAX_DISTANCE 10000


# define WHI 0xf9fcfc
# define BLK 0x000000
# define GREY 0x808080
# define GREN 0x009300
# define ORNG 0xff9300
# define RED 0xff0000

# define R_LEFT 123
# define R_RIGHT 124
# define LEFT_K 0
# define RIGHT_K 2
# define DOWN_K 1
# define UP_K 13

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
	char	**map;	// the map
	char	*no;	//no pointer
	char	*we;	//we pointer
	char	*so;	//so pointer
	char	*ea;	//ea pointer
	char	*f;		//flor color
	char	*c;		//color pinter
	int		p_x;	//player position int map
	int		p_y;	//player position int map
	int		map_h;	//map hight
	int		map_w;	//map wight
	t_col	*col;
}t_data;

typedef struct s_player
{
	int		plyr_x;	//player x pixel
	int		plyr_y;	//player y pixel
	float	angle;	//player rotation angel
	int		rot_s;	//player rotation_speed
	int		l_r;	//player rotation_direction
	int		u_d;	//player movemment_direction
	char	direc;	//player direction
}t_player;

typedef struct s_ray
{
	int		x;
	int		y;
}t_ray;
typedef struct s_mlx
{
	void		*img;	// image mlx pointer
	void		*win;	// window mlx pointer
	void		*mlx_p;	// mlx pointer
	char		*addr;	// mlx image address
	int			bits_per_pixel; //mlx img bits
	int			line_length;	//mlx line_lenght
	int			endian;			//mlx indian
	t_data		*dt;
	t_ray		*ray;
	t_player	*ply;
}t_mlx;

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
void	ft_free_data(t_data *dt, t_map *map, int *i, int j);
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
char	*ft_strtrim_back(char *s1, char *set);
void	get_h_w(t_mlx *mlx);
//execution.c
void	execution(t_data *dt);
#endif
