/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:53:10 by afatir            #+#    #+#             */
/*   Updated: 2023/12/05 10:58:02 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft_gcl_ptf/libft.h"
# include "MLXGLFW/MacOS/mlx/MLX42.h"

# define S_W 1900
# define S_H 1000
# define TILE_SIZE_R 16
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 2

# define BLK 0x000000FF
# define GREY 0x808080
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFFF

typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_txtr
{
	char			*key;
	char			*value;
	struct s_txtr	*next;
}	t_txtr;

typedef struct s_data
{
	char	**map2d;
	int		rows;
	int		cols;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
	char	**ff;
	char	**cc;
	int		fd;
	int		i;
	char	*line;
	char	*ture;
	char	*map;
	char	**ture2d;
	char	**sq_map;
	char	**rgb;
	t_txtr	*t;
}	t_data;

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
}	t_player;

typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*mlx_p;
	t_data			*dt;
	t_ray			*ray;
	t_player		*ply;
	t_tex			*tex;
	t_txtr			*l_ture;
	mouse_mode_t	mouse_mode;
}	t_mlx;

/////////////////////////////PARSING/////////////////////////////
//o_list.c
char	*removespaces(char *str);
int		check_duplicat(t_data *m);
void	ft_skipp(int *i, const char *p_str, int *sign);
int		valid_map(t_data *m);
// o_map.c
int		getsize_largline(char **map);
int		getsizemap(char **map);
char	*fixline(char *line, int maxlen);
int		h_map(char **map);
int		v_map(char **map);
// outils.c 
int		checkcolorvalues(char **rgb);
void	ft_process_rgb_color(t_txtr *tmp, t_data *m);
// p_map.c
int		if_surrounded(char *line);
int		if_validmap(char *line, int *flag);
int		suroundedbyone(char **map);
int		check_color_textures(char *line);
int		check_l_surroundedbyone(char *line);
// p_map1.c
char	*getmap(t_data *m);
int		read_map_(t_data *m, int count);
void	freeme(char *ture, char *line, int fd);
int		read_map(char *av, t_data *m, int *count);
//  p_map2.c
char	*getlastline(char **map);
int		check_first_last_line(char **map);
int		check_countture(t_data *m, int count);
// p_textures1.c
int		check_ifvalid(char *line);
int		checktures_space_tab(char **ture2d, int count);
int		check_pos_ofv(char *line);
int		count_vergules(char *rgb);
int		parse_rgb(char **ture2d);
// p_textures2.c
int		get_index(char *line, int i);
t_txtr	*new_texture(char *line);
void	lst_back_ture(t_txtr **l_ture, t_txtr *new);
int		lst_ture(t_data *m, t_txtr **l_ture);
//  par1.c
void	get_x_y_player(t_data *m);
void	free_2d(char **m);
int		checkextension(char *fname);
void	freelist(t_txtr **head);
// parsing.c
void	free_m(t_mlx *mlx);
int		color_ture(t_data *m, t_txtr *l_ture);
void	free_map(t_data *m);
int		parsing(int ac, char **av, t_data *m, t_txtr *l_ture);
/////////////////////////////BONUS/////////////////////////////
//execfree.c
void	ft_delete_tex_bonus(t_tex *tex);
void	ft_exit_bonus(t_mlx *mlx);
//mouvement.c
void	rotate_player_bonus(t_mlx *mlx, int i);
void	move_player_bonus(t_mlx *mlx, double move_x, double move_y);
void	cub_hook_bonus(t_mlx *mlx, double move_x, double move_y);
void	ft_reles_bonus(mlx_key_data_t keydata, t_mlx *mlx);
void	key_press_bonus(mlx_key_data_t keydata, void *ml);
//2dmap.c
void	get_angle_bonus(t_mlx *mlx);
void	draw_map_tile2d_bonus(t_mlx *mlx);
void	draw_win_bonus(t_mlx *mlx, int x, int y, int color);
void	draw_player_bonus(t_mlx *mlx, int x_p, int y_p, int color);
//execution.c
void	drow_map_pixel_bonus(void *mlxl);
int		checkload_bonus(t_txtr *list);
int		load_texture(t_tex *tex, t_txtr *l_ture);
void	my_mouse_bonus(void *param);
int		execution_bonus(t_data *dt);
// raycasting.c
int		inter_check_bonus(float angle, float *inter, float *step, int is_h);
int		wall_hit_bonus(float x, float y, t_mlx *mlx);
float	get_h_inter_bonus(t_mlx *mlx, float angl);
float	get_v_inter_bonus(t_mlx *mlx, float angl);
void	cast_rays_bonus(t_mlx *mlx);
// render2.c
int		get_rgba_bonus(int r, int g, int b, int a);
int		reverse_bytes_bonus(int c);
void	my_mlx_pixel_put_bonus(t_mlx *mlx, int x, int y, int color);
float	nor_angle_bonus(float angle);
int		unit_circle_bonus(float angle, char c);
// render.c
double	get_x_o_bonus(mlx_texture_t	*texture, t_mlx *mlx);
void	draw_floor_ceiling_bonus(t_mlx *mlx, int ray, int t_pix, int b_pix);
void	draw_wall_bonus(t_mlx *mlx, int t_pix, int b_pix, double wall_h);
void	render_wall_bonus(t_mlx *mlx, int ray);
#endif
