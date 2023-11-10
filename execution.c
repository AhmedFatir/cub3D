/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/10 21:13:00 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= (SIZE_W * mlx->dt->map_w) || y < 0 || y >= (SIZE_H * mlx->dt->map_h))
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
	int	x_m;
	int	y_m = y;
	int		flag;
	flag = 0;
	while (y_m < (y+SIZE_H))
	{
		x_m = x;
		if (!flag)
		{	
			while (x_m < (x+SIZE_W))
				my_mlx_pixel_put(mlx, x_m++, y_m, BLK);
			flag = 1;
		}
		else
		{		
			while (x_m < (x+SIZE_W))
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
	x_p -= SIZE_W/2;
	y_p -= SIZE_H/2;

	y = SIZE_H/3;
	while (y < (SIZE_H - SIZE_H/3))
	{
		x = SIZE_W/3;
		while (x < (SIZE_W - SIZE_W/3))
			my_mlx_pixel_put(mlx, x_p + x++, y_p + y, color);
		y++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void cast_rays(t_mlx *mlx)
{
	float ray_;
	float ray_x;
	float ray_y;
	int hit_wall;
	int mapX;
	int mapY;
	float stepX;
	float stepY;
	float nextX;
	float nextY;
	float t;
	float raw_distance_to_wall;

	const float FOV_rad = FOV * (M_PI / 180.0); // Convert the field of view (FOV) from degrees to radians.
	float ray__increment = FOV_rad / NUM_RAYS; // Calculate the  increment for each ray based on the FOV.

	int ray = 0;
	while (ray < NUM_RAYS)
	{ // Loop through each ray that needs to be cast.
		ray_ = mlx->ply->angle - (FOV_rad / 2) + (ray * ray__increment); // Calculate the  of the current ray.
		ray_ = fmod(ray_, 2 * M_PI); // Normalize the  between 0 and 2*PI.
		if (ray_ < 0)
			ray_ += 2 * M_PI; // Correct the  if it is negative.

		ray_x = mlx->ply->plyr_x; // Starting X position of the ray, player's X position.
		ray_y = mlx->ply->plyr_y; // Starting Y position of the ray, player's Y position.
		hit_wall = 0; // Flag to check if the wall is hit.
		raw_distance_to_wall = 0; // Distance to the wall without fish-eye correction.

		while (!hit_wall && raw_distance_to_wall < MAX_DISTANCE)
		{ // Cast the ray until a wall is hit or max distance is reached.
			ray_x += cos(ray_) * RAY_STEP; // Increment ray's X position based on the ray's .
			ray_y += sin(ray_) * RAY_STEP; // Increment ray's Y position based on the ray's .
			raw_distance_to_wall += RAY_STEP; // Increase the distance to the wall.

			mapX = floor(ray_x / TILE_SIZE); // Convert ray's X position to map coordinates.
			mapY = floor(ray_y / TILE_SIZE); // Convert ray's Y position to map coordinates.

			// Check if ray is out of bounds of the map.
			if (mapX < 0 || mapX >= mlx->dt->map_w || mapY < 0 || mapY >= mlx->dt->map_h)
			{
				hit_wall = 1; // Set flag to true because it's out of bounds.
				raw_distance_to_wall = MAX_DISTANCE; // Set distance to max to stop the loop.
				break; // Exit the loop.
			}

			// Check if the ray has hit a wall on the map.
			if (mlx->dt->map[mapY][mapX] == '1')
			{
				hit_wall = 1; // Wall is hit, set flag to true.
				break; // Exit the loop as the wall is hit.
			}
		}

		// Draw the ray for visualization on a 2D map.
		stepX = cos(ray_) * RAY_STEP; // Calculate the step size for X based on the .
		stepY = sin(ray_) * RAY_STEP; // Calculate the step size for Y based on the .
		nextX = mlx->ply->plyr_x; // Starting X position for drawing.
		nextY = mlx->ply->plyr_y; // Starting Y position for drawing.
		t = 0; // A variable to keep track of the distance while drawing.
		while (t < raw_distance_to_wall)
		{ // Draw the ray until the hit distance.
			int pixelX = (int)(nextX); // Convert the next X position to pixel coordinates.
			int pixelY = (int)(nextY); // Convert the next Y position to pixel coordinates.
			my_mlx_pixel_put(mlx, pixelX, pixelY, RED); // Place a pixel on the map for visualization.
			nextX += stepX; // Move to the next X position.
			nextY += stepY; // Move to the next Y position.
			t += RAY_STEP; // Increase the drawn distance.
		}
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

	y = 0;
	y_p = 0;
	while (y < mlx->dt->map_h)
	{
		x = 0;
		x_p = 0;
		while (mlx->dt->map[y][x])
		{
			char c = mlx->dt->map[y][x];
			if (c == '1')
				draw_win(mlx, x_p, y_p, GREY);
			else
				draw_win(mlx, x_p, y_p, WHI);
			x++;
			x_p += SIZE_W;
		}
		y++;
		y_p += SIZE_H;
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
	mlx->img = mlx_new_image(mlx->mlx_p, (mlx->dt->map_w * SIZE_H), (mlx->dt->map_h * SIZE_W));
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

void	init_player(t_mlx *mlx)
{	mlx->ply->angle = M_PI / 2;
	mlx->ply->plyr_x = (mlx->dt->p_x * SIZE_W) + SIZE_W/2;
	mlx->ply->plyr_y = (mlx->dt->p_y * SIZE_H) + SIZE_H/2;
	ft_printf("%d----%d\n", mlx->ply->plyr_x , mlx->ply->plyr_y);

}

void	execution(t_data *dt)
{
	t_mlx	mlx;

	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.dt = dt;
	mlx.mlx_p = mlx_init();
	get_h_w(&mlx);
	mlx.win = mlx_new_window(mlx.mlx_p, (mlx.dt->map_w * SIZE_H), (mlx.dt->map_h * SIZE_W), "cub3D");
	mlx.img = mlx_new_image(mlx.mlx_p, (mlx.dt->map_w * SIZE_H), (mlx.dt->map_h * SIZE_W));
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	init_player(&mlx);
	drow_map_pixel(&mlx);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}