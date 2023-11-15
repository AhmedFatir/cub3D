/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/15 15:32:07 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    if (x < 0)
        x = 0;
    else if (x >= mlx->screenWidth)
        x = mlx->screenWidth - 1;
    if (y < 0)
        y = 0;
    else if (y >= mlx->screenHeight)
        y = mlx->screenHeight - 1;
    char *dst;
    dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 1;
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	print_error("Game closed\n", &i);
	ft_free_data(mlx->dt, NULL, &i, 0);
	free(mlx->ply);
	exit(0);
	return (0);
}

void draw_win(t_mlx *mlx, int x, int y, int color)
{
	int		x_m;
	int		y_m;
	int		flag;

	y_m = y;
	flag = 0;
	while (y_m < (y+TILE_SIZE))
	{
		x_m = x;
		if (!flag)
		{	
			while (x_m < (x+TILE_SIZE))
				my_mlx_pixel_put(mlx, x_m++, y_m, BLK);
			flag = 1;
		}
		else
		{		
			while (x_m < (x+TILE_SIZE))
				my_mlx_pixel_put(mlx, x_m++, y_m, color);
			my_mlx_pixel_put(mlx, x_m-1, y_m, BLK);
		}
		y_m++;
	}
}

void drow_player(t_mlx *mlx, int x_p, int y_p, int color)
{
	int		x;
	int		y;
	x_p -= TILE_SIZE/2;
	y_p -= TILE_SIZE/2;
	y = TILE_SIZE/3;
	while (y < (TILE_SIZE - TILE_SIZE/3))
	{
		x = TILE_SIZE/3;
		while (x < (TILE_SIZE - TILE_SIZE/3))
			my_mlx_pixel_put(mlx, x_p + x++, y_p + y, color);
		y++;
	}
}
void map_2d(t_mlx *mlx, int raw_distance_to_wall)
{
	float	s_x;
	float	s_y;
	float	t;
	mlx->ray->ray_x = cos(mlx->ray->ray_ngl) * RAY_STEP; // Calculate the step size for X based on the ray's angle.
	mlx->ray->ray_y = sin(mlx->ray->ray_ngl) * RAY_STEP; // Calculate the step size for Y based on the ray's angle.
	s_x = mlx->ply->plyr_x; // Starting X position for drawing.
	s_y = mlx->ply->plyr_y; // Starting Y position for drawing.
	t = 0; // A variable to keep track of the distance while drawing.
	while (t < raw_distance_to_wall)
	{ // Draw the ray until the hit distance.
		my_mlx_pixel_put(mlx, (int)s_x, (int)s_y, RED); // Place a pixel on the map for visualization.
		s_x += mlx->ray->ray_x; // Move to the next X position.
		s_y += mlx->ray->ray_y; // Move to the next Y position.
		t += RAY_STEP; // Increase the drawn distance.
	}
}
/////////////////////////////////////////////////////////////
t_tex	*get_texu(t_mlx *mlx)
{
    // Assuming you have four textures: tex_north, tex_south, tex_east, tex_west
    // You need to load these textures in your initialization code

    t_tex *tex;

    // Determine which direction the ray is facing
    double ray_angle = fmod(mlx->ray->ray_ngl, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;

    // Define the angle ranges for each direction
    double angle_north = M_PI / 2;  // Adjust the angle range for the NORTH texture
    double angle_south = 3 * M_PI / 2;
    double angle_east = 0;
    double angle_west = M_PI;

    // Determine which texture to use based on the ray's direction
    if ((ray_angle >= angle_north && ray_angle < angle_south) || (ray_angle >= angle_south + 2 * M_PI))
        tex = &mlx->tex_no;
    else if (ray_angle >= angle_east && ray_angle < angle_west)
        tex = &mlx->tex_ea;
    else if (ray_angle >= angle_west && ray_angle < angle_north)
        tex = &mlx->tex_we;
    else
        tex = &mlx->tex_so;

    return tex;
}

void draw_wall(t_mlx *mlx, int ray_index, int wall_top_pixel, int wall_bottom_pixel)
{
    int y = wall_top_pixel;
    t_tex *tex = get_texu(mlx);

    double y_t;
    double x_t;

    // Calculate the texture coordinate based on the ray's angle
    double ray_angle = fmod(mlx->ray->ray_ngl, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;

    // Adjust these values based on your texture size and the desired mapping
    int texture_width = tex->width;
    int texture_height = tex->height;

    // Calculate the texture coordinate based on the wall height
    x_t = ((double)ray_index / mlx->screenWidth) * texture_width;

    while (y <= wall_bottom_pixel)
    {
        // Calculate the texture coordinate based on the wall height
        y_t = ((double)(y - wall_top_pixel) / (wall_bottom_pixel - wall_top_pixel)) * texture_height;

        // Ensure the texture coordinates are within bounds
        if (x_t >= 0 && x_t < texture_width && y_t >= 0 && y_t < texture_height)
        {
            int color = tex->addr[(int)y_t * texture_width + (int)x_t];
            my_mlx_pixel_put(mlx, ray_index, y++, color);
        }
        else
        {
            // Handle the case where the texture coordinates are outside bounds
            // You might want to set a default color or do some error handling
            break;
        }
    }
}

///////////////////////////////////////////////////////////
void draw_floor(t_mlx *mlx, int x, int wall_end)
{
    int i = wall_end;
    while (i < mlx->screenHeight)
    {
        my_mlx_pixel_put(mlx, x, i, FLOOR_COLOR);
        i++;
    }
}

void draw_ceiling(t_mlx *mlx, int x, int wall_start)
{
    int i = 0;
    while (i < wall_start)
    {
        my_mlx_pixel_put(mlx, x, i, CEILING_COLOR);
        i++;
    }
}

void render_walls(t_mlx *mlx, int ray_index, float distance)
{
    double wall_height;
	double wall_bottom_pixel;
	double wall_top_pixel;
	
    // Apply fish-eye correction to the distance
    distance *= cos(fabs(mlx->ray->ray_ngl - mlx->ply->angle));

    // Calculate wall height using a standard fish-eye correction formula
    wall_height = (TILE_SIZE * mlx->screenHeight) / (2 * distance * tan(FOV_RAD / 2));
    
    // Calculate the top and bottom pixels of the wall on the screen
    wall_bottom_pixel = mlx->screenHeight / 2 + wall_height / 2;
    wall_top_pixel = mlx->screenHeight / 2 - wall_height / 2;

    // Draw the wall, floor, and ceiling
    draw_floor(mlx, ray_index, wall_bottom_pixel);
    draw_ceiling(mlx, ray_index, wall_top_pixel);
    draw_wall(mlx, ray_index, (int)wall_top_pixel, (int)wall_bottom_pixel);
}


void cast_rays(t_mlx *mlx)
{
	int		hit_wall;
	int		mapX;
	int		mapY;
	float	distance;
	int		ray;

	ray = 0;
	while (ray < NUM_RAYS)
	{ // Loop through each ray that needs to be cast.
		mlx->ray->ray_ngl = mlx->ply->angle - (FOV_RAD / 2) + (ray * RAY_INC); // Calculate the  of the current ray.
		mlx->ray->ray_ngl = fmod(mlx->ray->ray_ngl, 2 * M_PI); // Normalize the  between 0 and 2*PI.
		if (mlx->ray->ray_ngl < 0)
			mlx->ray->ray_ngl += 2 * M_PI; // Correct the  if it is negative.

		mlx->ray->ray_x = mlx->ply->plyr_x; // Starting X position of the ray, player's X position.
		mlx->ray->ray_y = mlx->ply->plyr_y; // Starting Y position of the ray, player's Y position.
		hit_wall = 0; // Flag to check if the wall is hit.
		distance = 0; // Distance to the wall without fish-eye correction.

		while (!hit_wall && distance < MAX_DISTANCE)
		{ // Cast the ray until a wall is hit or max distance is reached.
			mlx->ray->ray_x += cos(mlx->ray->ray_ngl) * RAY_STEP; // Increment ray's X position based on the ray's .
			mlx->ray->ray_y += sin(mlx->ray->ray_ngl) * RAY_STEP; // Increment ray's Y position based on the ray's .
			distance += RAY_STEP; // Increase the distance to the wall.
			mapX = floor(mlx->ray->ray_x / TILE_SIZE); // Convert ray's X position to map coordinates.
			mapY = floor(mlx->ray->ray_y / TILE_SIZE); // Convert ray's Y position to map coordinates.
			if (mapX < 0 || mapX >= mlx->dt->map_w || mapY < 0 || mapY >= mlx->dt->map_h)
			{// Check if ray is out of bounds of the map.
				hit_wall = 1; // Set flag to true because it's out of bounds.
				// distance = MAX_DISTANCE; // Set distance to max to stop the loop.
				break; // Exit the loop.
			}
			if (mlx->dt->map[mapY][mapX] == '1')
			{// Check if the ray has hit a wall on the map.
				hit_wall = 1; // Wall is hit, set flag to true.
				break; // Exit the loop as the wall is hit.
			}
		}
		render_walls(mlx, ray, distance);
		// map_2d(mlx, distance);
		ray++; // Move to the next ray.
	}
}

void	draw_map_tile2d(t_mlx *mlx)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;

	y = 0;
	y_p = 0;
	while (y < mlx->dt->map_h)
	{
		x = 0;
		x_p = 0;
		while (mlx->dt->map[y][x])
		{
			char c = mlx->dt->map[y][x];
			draw_win(mlx, x_p, y_p, WHI);
			if (c == '1')
				draw_win(mlx, x_p, y_p, GREY);
			x++;
			x_p += TILE_SIZE;
		}
		y++;
		y_p += TILE_SIZE;
	}
	drow_player(mlx, mlx->ply->plyr_x, mlx->ply->plyr_y, ORNG);
}

void	drow_map_pixel(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_p, mlx->win);
	mlx->img = mlx_new_image(mlx->mlx_p, (mlx->dt->map_w * TILE_SIZE), (mlx->dt->map_h * TILE_SIZE));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// draw_map_tile2d(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img, 0, 0);
}

void rotate_player_left(t_mlx *mlx)
{
	mlx->ply->angle -= ROTATION_SPEED;
	if (mlx->ply->angle < 0)
	{ // Normalize the  to be between 0 and 2*PI
		mlx->ply->angle += 2 * M_PI;
	}
}

void rotate_player_right(t_mlx *mlx)
{
	mlx->ply->angle += ROTATION_SPEED;
	if (mlx->ply->angle >= 2 * M_PI) 
	{ // Normalize the  to be between 0 and 2*PI
		mlx->ply->angle -= 2 * M_PI;
	}
}

void move_player(t_mlx *mlx, float move_x, float move_y)
{
    // Predict the future position
    int new_x = roundf(mlx->ply->plyr_x + move_x);
    int new_y = roundf(mlx->ply->plyr_y + move_y);

    // Calculate the map grid position for the new coordinates
    int map_grid_x = (new_x / TILE_SIZE);
    int map_grid_y = (new_y / TILE_SIZE);

    // Check if the new position is within the map bounds
    if (mlx->dt->map[map_grid_y][map_grid_x] != '1')
    {
        // No collision, update player position
        mlx->ply->plyr_x = new_x;
        mlx->ply->plyr_y = new_y;
    }
    // Else, do nothing (player stays in place due to collision)
}

int	cub_hook(t_mlx *mlx, int key)
{
	float	move_x;
	float	move_y;

	if (key == R_LEFT)
		rotate_player_left(mlx);
	else if (key == R_RIGHT)
		rotate_player_right(mlx);
	else if (key == RIGHT_K)
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_player(mlx, move_x, move_y);
	}
	else if (key == LEFT_K)
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_player(mlx, move_x, move_y);
	}
	else if (key == DOWN_K)
	{
	    move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
	    move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	    move_player(mlx, move_x, move_y);
	}
	else if (key == UP_K)
	{
	    move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
	    move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	    move_player(mlx, move_x, move_y);
	}
	drow_map_pixel(mlx);
	return (0);
}

int	ft_hook(int key,t_mlx *mlx)
{
	if (key == 53)
		ft_exit(mlx);
	else
		cub_hook(mlx, key);
	return (0);
}

void get_angle(t_mlx *mlx)
{
    char c;

    c = mlx->dt->map[mlx->dt->p_y][mlx->dt->p_x];
    if (c == 'N')
        mlx->ply->angle = 3 * M_PI / 2;
    if (c == 'S')
        mlx->ply->angle = M_PI / 2;
    if (c == 'E')
        mlx->ply->angle = 0;
    if (c == 'W')
        mlx->ply->angle = M_PI;
	mlx->ply->plyr_x = (mlx->dt->p_x * TILE_SIZE);
	mlx->ply->plyr_y = (mlx->dt->p_y * TILE_SIZE);
}
void	get_tex(t_mlx *mlx)
{
	mlx->tex_no.img = mlx_xpm_file_to_image(mlx->mlx_p, "textures/no.xpm", \
		&mlx->tex_no.width, &mlx->tex_no.height);
	if(!mlx->tex_no.img)
		exit(9);

	mlx->tex_so.img = mlx_xpm_file_to_image(mlx->mlx_p, "textures/so.xpm", \
		&mlx->tex_so.width, &mlx->tex_so.height);
	if(!mlx->tex_so.img)
		exit(9);

	mlx->tex_ea.img = mlx_xpm_file_to_image(mlx->mlx_p, "textures/ea.xpm", \
		&mlx->tex_ea.width, &mlx->tex_ea.height);
	if(!mlx->tex_ea.img)
		exit(9);

	mlx->tex_we.img = mlx_xpm_file_to_image(mlx->mlx_p, "textures/we.xpm", \
		&mlx->tex_we.width, &mlx->tex_we.height);
	if(!mlx->tex_we.img)
		exit(9);
	/////////////////
	mlx->tex_no.addr = (int *)mlx_get_data_addr(mlx->tex_no.img, &mlx->tex_no.bits_per_pixel\
		, &mlx->tex_no.line_length, &mlx->tex_no.endian);

	mlx->tex_so.addr = (int *)mlx_get_data_addr(mlx->tex_so.img, &mlx->tex_so.bits_per_pixel\
		, &mlx->tex_so.line_length, &mlx->tex_so.endian);

	mlx->tex_ea.addr = (int *)mlx_get_data_addr(mlx->tex_ea.img, &mlx->tex_ea.bits_per_pixel\
		, &mlx->tex_ea.line_length, &mlx->tex_ea.endian);

	mlx->tex_we.addr = (int *)mlx_get_data_addr(mlx->tex_we.img, &mlx->tex_we.bits_per_pixel\
		, &mlx->tex_we.line_length, &mlx->tex_we.endian);
}
void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.dt = dt;
	mlx.mlx_p = mlx_init();
	get_h_w(&mlx);
	mlx.win = mlx_new_window(mlx.mlx_p, (mlx.dt->map_w * TILE_SIZE), (mlx.dt->map_h * TILE_SIZE), "cub3D");
	get_tex(&mlx);
	get_angle(&mlx);
	drow_map_pixel(&mlx);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}