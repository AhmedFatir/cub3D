/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
/*   Updated: 2023/11/23 04:15:35 by afatir           ###   ########.fr       */
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

# define S_W 1440
# define S_H 720
# define TILE_SIZE 48
# define FOV 60
# define ROTATION_SPEED 0.05
# define PLAYER_SPEED 5

# define BLK 0x000000
# define GREY 0x808080
# define BLU 0x87CEEB
# define GREN 0x008000
# define ORNG 0xFF9300
# define RED 0xFF0000
# define WHI 0xFFFFFF

# define R_LEFT 123
# define R_RIGHT 124
# define LEFT_K 0
# define RIGHT_K 2
# define DOWN_K 1
# define UP_K 13
# define ESC 53

typedef struct s_map
{
	char			*line;
	int				index;
	struct s_map	*next;
}t_map;

typedef struct s_tex
{
	void		*img;
	void		*mlx_p;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endi;
	int			height;
	int			width;
}t_tex;

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
	int		map_h;
	int		map_w;
	t_col	*col;
}t_data;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	float	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}t_player;

typedef struct s_ray
{
	int		ray_v;
	float	ray_ngl;
	float	horiz_x;
	float	horiz_y;
	float	vert_x;
	float	vert_y;
	float	ray_x;
	float	ray_y;
	float	distance;
}t_ray;

typedef struct s_mlx
{
	void		*img;
	void		*win;
	void		*mlx_p;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endi;
	t_data		*dt;
	t_ray		*ray;
	t_player	*ply;
	t_tex		tex_no;
	t_tex		tex_so;
	t_tex		tex_we;
	t_tex		tex_ea;
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
float	nor_angle(float angle);
int		is_sep(char c);
void	check_directions(char *line, int *j, int *i, t_info *n);
char	*ft_strtrim_back(char *s1, char *set);
void	get_h_w(t_mlx *mlx);
///////////////////////////////EXECUTION////////////////////////////
//mouvement.c
void	cub_hook(t_mlx *mlx, float move_x, float move_y);
int		ft_press(int key, t_mlx *mlx);
int		ft_release(int key, t_mlx *mlx);
void	move_player(t_mlx *mlx, float move_x, float move_y);
void	rotate_player(t_mlx *mlx, int i);
//2dmap.c
void	get_angle(t_mlx *mlx);
void	draw_map_tile2d(t_mlx *mlx);
void	draw_win(t_mlx *mlx, int x, int y, int color);
void	drow_player(t_mlx *mlx, int x_p, int y_p, int color);
void	draw_ray_2d(t_mlx *mlx, double angle, double distance, int color);
//execution.c
int		ft_exit(t_mlx *mlx);
void	execution(t_data *dt);
int		drow_map_pixel(t_mlx *mlx);
void	get_tex(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
// raycasting.c
void	cast_rays(t_mlx *mlx);
// render.c
void	render_wall(t_mlx *mlx, int ray);
#endif
