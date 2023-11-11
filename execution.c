/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/11 15:14:09 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= (TILE_SIZE * mlx->dt->map_w) || y < 0 || y >= (TILE_SIZE * mlx->dt->map_h))
	{
		ft_printf ("(%d)-----(%d)\n", x, y);
		ft_printf ("NTCHAWFO\n");
		exit(0);
	}
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////

void render_wall(t_mlx *mlx, int ray_index, float raw_distance_to_wall)
{
    // Constants for colors
    int wall_color = 0xFFFFFF;     // White color for walls
    int floor_color = 0x008000;    // Green color for the floor
    int ceiling_color = 0x87CEEB;  // Sky Blue color for the ceiling

    // Calculate wall height on the screen
    int screenHeight = mlx->dt->map_h * TILE_SIZE; // Adjust this based on your actual screen dimensions
    int wall_height = (int)(screenHeight / raw_distance_to_wall);

    // Calculate the starting and ending screen coordinates for the wall
    int wall_start = (screenHeight - wall_height) / 2;
    int wall_end = wall_start + wall_height;

    // Ensure wall_start and wall_end are within screen bounds
    wall_start = fmax(0, wall_start);
    wall_end = fmin(screenHeight, wall_end);

    // Draw the entire wall segment with a vertical line
    for (int row = wall_start; row < wall_end; ++row)
    {
        my_mlx_pixel_put(mlx, ray_index, row, wall_color);
    }

    // Draw the ceiling and floor
    for (int row = 0; row < wall_start; ++row)
    {
        my_mlx_pixel_put(mlx, ray_index, row, ceiling_color);
    }

    for (int row = wall_end; row < screenHeight; ++row)
    {
        my_mlx_pixel_put(mlx, ray_index, row, floor_color);
    }
}

void cast_rays(t_mlx *mlx)
{
	int		hit_wall;
	int		mapX;
	int		mapY;
	float	raw_distance_to_wall;
	int		ray;

	ray = 0;
	while (ray < NUM_RAYS)
	{ // Loop through each ray that needs to be cast.
		mlx->ray->ray_ngl = mlx->ply->angle - (FOV_RD / 2) + (ray * RAY_INC); // Calculate the  of the current ray.
		mlx->ray->ray_ngl = fmod(mlx->ray->ray_ngl, 2 * M_PI); // Normalize the  between 0 and 2*PI.
		if (mlx->ray->ray_ngl < 0)
			mlx->ray->ray_ngl += 2 * M_PI; // Correct the  if it is negative.
		mlx->ray->ray_x = mlx->ply->plyr_x; // Starting X position of the ray, player's X position.
		mlx->ray->ray_y = mlx->ply->plyr_y; // Starting Y position of the ray, player's Y position.
		hit_wall = 0; // Flag to check if the wall is hit.
		raw_distance_to_wall = 0; // Distance to the wall without fish-eye correction.
		while (!hit_wall && raw_distance_to_wall < MAX_DISTANCE)
		{ // Cast the ray until a wall is hit or max distance is reached.
			mlx->ray->ray_x += cos(mlx->ray->ray_ngl) * RAY_STEP; // Increment ray's X position based on the ray's .
			mlx->ray->ray_y += sin(mlx->ray->ray_ngl) * RAY_STEP; // Increment ray's Y position based on the ray's .
			raw_distance_to_wall += RAY_STEP; // Increase the distance to the wall.
			mapX = floor(mlx->ray->ray_x / TILE_SIZE); // Convert ray's X position to map coordinates.
			mapY = floor(mlx->ray->ray_y / TILE_SIZE); // Convert ray's Y position to map coordinates.
			if (mapX < 0 || mapX >= mlx->dt->map_w || mapY < 0 || mapY >= mlx->dt->map_h)
			{// Check if ray is out of bounds of the map.
				hit_wall = 1; // Set flag to true because it's out of bounds.
				raw_distance_to_wall = MAX_DISTANCE; // Set distance to max to stop the loop.
				break; // Exit the loop.
			}
			if (mlx->dt->map[mapY][mapX] == '1')
			{// Check if the ray has hit a wall on the map.
				hit_wall = 1; // Wall is hit, set flag to true.
				break; // Exit the loop as the wall is hit.
			}
		}
		/////////////2D MAP////////////////////////
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
		/////////////2D MAP////////////////////////

		/////////////3D MAP///////////////////////
		// render_wall(mlx, ray, raw_distance_to_wall);
		/////////////3D MAP///////////////////////
		ray++; // Move to the next ray.
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void	drow_map_pixel(t_mlx *mlx)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;
	static int flag = 0;

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
			if (valide_symbols(c) == 2 && !flag)
			{
				mlx->ply->plyr_x = x_p + TILE_SIZE/2;
				mlx->ply->plyr_y = y_p + TILE_SIZE/2;
				flag = 1;
			}
			x++;
			x_p += TILE_SIZE;
		}
		y++;
		y_p += TILE_SIZE;
	}
	drow_player(mlx, mlx->ply->plyr_x, mlx->ply->plyr_y, ORNG);
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
	float new_x = roundf(mlx->ply->plyr_x + move_x);
	float new_y = roundf(mlx->ply->plyr_y + move_y);
	// Calculate the map grid position for the new coordinates
	int map_grid_x = (new_x / TILE_SIZE);
	int map_grid_y = (new_y / TILE_SIZE);
	// Check if the map grid position is a wall
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

	mlx_destroy_image(mlx->mlx_p, mlx->img);
	mlx_clear_window(mlx->mlx_p, mlx->win);
	mlx->img = mlx_new_image(mlx->mlx_p, (mlx->dt->map_w * TILE_SIZE), (mlx->dt->map_h * TILE_SIZE));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (key == -1)
		return (0);
	if (key == R_LEFT)
		rotate_player_left(mlx);
	else if (key == R_RIGHT)
		rotate_player_right(mlx);
	else if (key == LEFT_K) 
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_player(mlx, move_x, move_y);
	}
	else if (key == RIGHT_K)
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

void	get_angle(t_mlx *mlx)
{
	char	c;

	c = mlx->dt->map[mlx->dt->p_x][mlx->dt->p_y];
	if (c == 'N')
		mlx->ply->angle = 3 * M_PI/2;
	if (c == 'S')
		mlx->ply->angle = M_PI/2;
	if (c == 'E')
		mlx->ply->angle = 2 * M_PI;
	if (c == 'W')
		mlx->ply->angle = M_PI;
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
	mlx.img = mlx_new_image(mlx.mlx_p, (mlx.dt->map_w * TILE_SIZE), (mlx.dt->map_h * TILE_SIZE));
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	get_angle(&mlx);
	drow_map_pixel(&mlx);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}