/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:08 by afatir            #+#    #+#             */
/*   Updated: 2023/11/05 15:28:13 by afatir           ###   ########.fr       */
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

void cast_rays(t_mlx *mlx) {
	const float FOV_rad = FOV * (PI / 180.0);
	float ray_angle_increment = FOV_rad / NUM_RAYS;

	for (int ray = 0; ray < NUM_RAYS; ray++) {
		float ray_angle = mlx->ply->rot_angele - (FOV_rad / 2) + (ray * ray_angle_increment);
		ray_angle = fmod(ray_angle, 2 * PI); // Normalize angle
		if (ray_angle < 0) ray_angle += 2 * PI;

		float ray_x = mlx->ply->plyr_x;
		float ray_y = mlx->ply->plyr_y;
		int hit_wall = 0;
		float raw_distance_to_wall = 0; // Raw distance without fish-eye correction

		while (!hit_wall && raw_distance_to_wall < MAX_DISTANCE) {
			ray_x += cos(ray_angle) * RAY_STEP;
			ray_y += sin(ray_angle) * RAY_STEP;
			raw_distance_to_wall += RAY_STEP;

			int mapX = (int)(ray_x / TILE_SIZE);
			int mapY = (int)(ray_y / TILE_SIZE);

			// Check if ray is out of bounds
			if (mapX < 0 || mapX >= mlx->dt->map_w || mapY < 0 || mapY >= mlx->dt->map_h) {
				hit_wall = 1; // Out of bounds
				raw_distance_to_wall = MAX_DISTANCE;
				break; // Stop the while loop
			}

			// Check if ray has hit a wall
			if (mlx->dt->map[mapY][mapX] == '1') {
				hit_wall = 1; // Wall is hit, stop the ray
				
				// Do not apply the fish-eye correction here, it will be applied when rendering the wall slice
				break; // Stop the while loop when a wall is hit
			}
		}

		// Draw the 2D ray for visualization
		float stepX = cos(ray_angle) * RAY_STEP;
		float stepY = sin(ray_angle) * RAY_STEP;
		float nextX = mlx->ply->plyr_x;
		float nextY = mlx->ply->plyr_y;

		for (float t = 0; t < raw_distance_to_wall; t += RAY_STEP) {
			int pixelX = (int)(nextX);
			int pixelY = (int)(nextY);
			my_mlx_pixel_put(mlx, pixelX, pixelY, RED); // Color the ray red for visibility
			nextX += stepX;
			nextY += stepY;
		}

		// When rendering the 3D wall slice, apply the fish-eye correction here
		// float corrected_distance_to_wall = raw_distance_to_wall * cos(mlx->ply->rot_angele - ray_angle);
		// Use corrected_distance_to_wall to calculate the height of the wall slice...
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void rotate_player_left(t_mlx *mlx) {
	mlx->ply->rot_angele -= ROTATION_SPEED;
	if (mlx->ply->rot_angele < 0) { // Normalize the angle to be between 0 and 2*PI
		mlx->ply->rot_angele += 2 * PI;
	}
}

void rotate_player_right(t_mlx *mlx) {
	mlx->ply->rot_angele += ROTATION_SPEED;
	if (mlx->ply->rot_angele >= 2 * PI) { // Normalize the angle to be between 0 and 2*PI
		mlx->ply->rot_angele -= 2 * PI;
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

void move_player(t_mlx *mlx, float move_x, float move_y) {
	// Predict the future position
	float new_x = mlx->ply->plyr_x + move_x;
	float new_y = mlx->ply->plyr_y + move_y;

	// Calculate the map grid position for the new coordinates
	int map_grid_x = (int)(new_x / TILE_SIZE);
	int map_grid_y = (int)(new_y / TILE_SIZE);

	// Check if the map grid position is a wall
	if (mlx->dt->map[map_grid_y][map_grid_x] != '1') {
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
	if (key == R_RIGHT)
		rotate_player_right(mlx);


	if (key == LEFT_K) 
	{
		move_x = -sin(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_y = cos(mlx->ply->rot_angele) * PLAYER_SPEED;
	   move_player(mlx, move_x, move_y);
	}

	else if (key == RIGHT_K)
	{
		move_x = sin(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_player(mlx, move_x, move_y);
	}

	else if (key == DOWN_K)
	{
		move_x = cos(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_y = sin(mlx->ply->rot_angele) * PLAYER_SPEED;	
		move_player(mlx, move_x, move_y);
	}

	else if (key == UP_K)
	{
		move_x = -cos(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->rot_angele) * PLAYER_SPEED;
		move_player(mlx, move_x, move_y);
	}
	
	drow_map_pixel(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img, 0, 0);
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
{	mlx->ply->rot_angele = M_PI / 2;
	mlx->ply->plyr_x = (mlx->dt->p_x * SIZE_W) + SIZE_W/2;
	mlx->ply->plyr_y = (mlx->dt->p_y * SIZE_H) + SIZE_H/2;
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

	

	/////////////////////////////////////////////////
	init_player(&mlx);
	drow_map_pixel(&mlx);
	cast_rays(&mlx);
	///////////////////////////
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 0, ft_hook, &mlx);
	mlx_loop(mlx.mlx_p);
}