/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:32:06 by afatir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/30 23:21:43 by afatir           ###   ########.fr       */
=======
/*   Updated: 2023/11/30 16:55:21 by khbouych         ###   ########.fr       */
>>>>>>> 9bfd40f3d26e871d79c461f4fb2723bc392e4e3c
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft_gcl_ptf/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define S_W 2000
<<<<<<< HEAD
# define S_H 1000
# define TILE_SIZE 15
# define TILE_SIZE_MAP 50
# define FOV 60
# define ROTATION_SPEED 0.02
# define PLAYER_SPEED 1
=======
# define S_H 1200
# define TILE_SIZE 64
# define FOV 60
# define ROTATION_SPEED 0.03
# define PLAYER_SPEED 5
>>>>>>> 9bfd40f3d26e871d79c461f4fb2723bc392e4e3c

# define BLK 0x000000FF
# define GREY 0x808080FF
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFFFFF

typedef struct s_tex
{
	mlx_texture_t*	no;
	mlx_texture_t*	so;
	mlx_texture_t*	we;
	mlx_texture_t*	ea;
}	t_tex;


typedef struct s_data
{
	char	**map2d;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
	char 	**ff;
	char 	**cc;
	int		fd;
	int		i;
	char	*line;
	char	*ture;
	char	*map;
	char	**ture2d;
	char	**sq_map;
	char	**rgb;
}t_data;

typedef struct s_txtr
{
	char			*key;
	char			*value;
	struct s_txtr	*next;
}t_txtr;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
	int		m_x;
	int		m_y;
}t_player;

typedef struct s_ray
{
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int flag;
}t_ray;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*mlx_p;
	t_data		*dt;
	t_ray		*ray;
	t_player	*ply;
	t_tex		*tex;
	t_txtr		*l_ture;
}t_mlx;

///////////////////////////////EXECUTION////////////////////////////
//mouvement.c
void printlist(t_txtr *l);
float	nor_angle(float angle);
void	cub_hook(t_mlx *mlx, double move_x, double move_y);
void	key_press(mlx_key_data_t keydata, void *ml);
void	move_player(t_mlx *mlx, double move_x, double move_y);
void	rotate_player(t_mlx *mlx, int i);
//2dmap.c
void	get_angle(t_mlx *mlx);
void	draw_map_tile2d(t_mlx *mlx);
void	draw_win(t_mlx *mlx, int x, int y, int color);
void	draw_player(t_mlx *mlx, int x_p, int y_p, int color);
void	draw_ray_2d(t_mlx *mlx, double angle, double distance, int color);
//execution.c
int		ft_exit(t_mlx *mlx);
void	execution(t_data *dt);
void	drow_map_pixel(void *mlxl);
void	get_tex(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
// raycasting.c
int	unit_circle(float angle, char c);
void	cast_rays(t_mlx *mlx);
// render.c
void	render_wall(t_mlx *mlx, int ray);

/////////////////////////////////////PARSING//////////////////////
//o_list.c
char	*removespaces(char *str);
int	check_duplicat(t_data *m);
// static void	ft_skipp(int *i, const char *p_str, int *sign);
int	ft_atoi(const char *str);
// char	*ft_strrchr(char *str, int c);
// o_map.c
int	getsize_largline(char **map);
int	getsizemap(char **map);
char	*fixline(char *line, int maxlen);
int	h_map(char **map);
int	v_map(char **map);
//outils_.c
// void	*ft_memset(void *s, int c, unsigned int len);
// void	*ft_calloc(unsigned int count, unsigned int size);
// char	*ft_substr(char *s, unsigned int start, unsigned int len);
char	*ft_strtrim(char *s1, char *set);
// outils.c 
// void	*ft_memcpy(void *dest, const void *src, unsigned int n);
// char	*ft_strdup(char *s1);
int	ft_isdigit(int c);
int	checkcolorvalues(char **rgb);
int	ft_process_rgb_color(t_txtr *tmp, t_data *m);
// p_map.c
int	if_surrounded(char *line);
int	if_validmap(char *line, int *flag);
int	suroundedbyone(char **map);
int	check_color_textures(char *line);
int	check_l_surroundedbyone(char *line);
// p_map1.c
char	*getmap(t_data *m);
int	read_map_(t_data *m, int count);
void	freeme(char *ture, char *line, int fd);
int	read_map(char *av, t_data *m, int *count);
//  p_map2.c
char	*getlastline(char **map);
int	check_first_last_line(char **map);
int	check_countture(t_data *m, int count);
// p_textures1.c
int	check_ifvalid(char *line);
int	checktures_space_tab(char **ture2d, int count);
int	check_pos_ofv(char *line);
int	count_vergules(char *rgb);
int	parse_rgb(char **ture2d);
// p_textures2.c
int	get_index(char *line, int i);
t_txtr	*new_texture(char *line);
t_txtr	*lst_back_ture(t_txtr *l_ture, t_txtr *new);
void	lst_back_ture2(t_txtr **l_ture, t_txtr *new);
int	lst_ture(t_data *m, t_txtr **l_ture);
//  par1.c
int	valid_map(t_data *m);
void	get_x_y_player(t_mlx *smlx, t_data *m);
void	free_2d(char **m);
void	free1(t_data *m, t_txtr *l_ture);
int	checkextension(char *fname);
// parsing.c
void	free_m(t_mlx *mlx);
int	color_ture(t_data *m, t_txtr *l_ture);
int	parsing(int ac, char **av, t_data *m, t_txtr *l_ture);
void	freelist(t_txtr **head);
#endif
