/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:36:01 by afatir            #+#    #+#             */
/*   Updated: 2023/11/16 18:43:13 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

t_tex	*get_texture(t_mlx *mlx)
{
    t_tex *tex;

    double ray_angle = fmod(mlx->ray->ray_ngl, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;

    double angle_north = M_PI / 2;
    double angle_south = 3 * M_PI / 2;
    double angle_east = 0;
    double angle_west = M_PI;

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
    t_tex *tex = get_texture(mlx);

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
    x_t = ((double)ray_index / mlx->sc_width) * texture_width;

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

void	draw_floor_ceiling(t_mlx *mlx, int x, int wall_end, int wall_start)
{
    int i = wall_end;
    while (i < mlx->sc_height)
    {
        my_mlx_pixel_put(mlx, x, i, FLOOR_COLOR);
        i++;
    }
    i = 0;
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
    wall_height = (TILE_SIZE * mlx->sc_height) / (2 * distance * tan(FOV_RAD / 2));
    
    // Calculate the top and bottom pixels of the wall on the screen
    wall_bottom_pixel = mlx->sc_height / 2 + wall_height / 2;
    wall_top_pixel = mlx->sc_height / 2 - wall_height / 2;
	draw_floor_ceiling(mlx, ray_index, wall_bottom_pixel, wall_top_pixel);
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
