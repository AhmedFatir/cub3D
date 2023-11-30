// #include "../include/cub3d.h"

// uint32_t	reverse_bytes(uint32_t num)
// {
// 	return (((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) \
// 	| ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000));
// }

// mlx_texture_t	*get_texture(t_ray ray, t_data *data)
// {
// 	if (!ray.is_verthit)
// 	{
// 		if (ray.rayangle > M_PI && ray.rayangle < 2 * M_PI)
// 			return (data->img_data->north);
// 		else
// 			return (data->img_data->south);
// 	}
// 	else
// 	{
// 		if (ray.rayangle > M_PI / 2 && ray.rayangle < 1.5 * M_PI)
// 			return (data->img_data->west);
// 		else
// 			return (data->img_data->east);
// 	}
// 	return (NULL);
// }

// void	put_pixels_helper(t_txtr_data *tx_data, \
// t_data *data, int start, mlx_texture_t *txtr)
// {
// 	tx_data->x_step = txtr->width / CUB_SIZE;
// 	tx_data->x_offset = ((int)((double)data->ray.x_hit * \
// 	tx_data->x_step) % txtr->width);
// 	if (data->ray.is_verthit)
// 	{
// 		tx_data->x_offset = ((int)((double)data->ray.y_hit * \
// 		tx_data->x_step) % txtr->width);
// 	}
// 	tx_data->y_step = (float)txtr->height / data->ray.wall_height;
// 	tx_data->first_pixel = ((start - (data->window_height / 2) \
// 	+ (data->ray.wall_height / 2)) * tx_data->y_step);
// }

void	draw_strip(t_data *data, int id, int start, int end)
{
	t_txtr_data		texture_data;
	mlx_texture_t	*txtr;
	uint32_t		*pixels;

	txtr = get_texture(data->ray, data);
	pixels = (uint32_t *)txtr->pixels;
	put_pixels_helper(&texture_data, data, start, txtr);
	while (start < end)
	{
		texture_data.y_offset = (int)texture_data.first_pixel;
		texture_data.color = pixels[texture_data.y_offset * txtr->height + \
		texture_data.x_offset];
		texture_data.first_pixel += texture_data.y_step;
		texture_data.color = reverse_bytes(texture_data.color);
		if (id >= 0 && id < data->window_width && start >= 0 \
		&& start < data->window_height)
			mlx_put_pixel(data->img, id, start, texture_data.color);
		start++;
	}
}

// void	wall_projection(t_data *data, int id)
// {
// 	float	distance_pp;
// 	int		start;
// 	int		end;

// 	distance_pp = (data->window_width / 2) / tan(data->fov / 2);
// 	data->ray.wall_height = distance_pp * (CUB_SIZE / (data->ray.distance * \
// 	cos(data->ray.rayangle - data->p_data->player_angle)));
// 	start = (data->window_height / 2) - ((int)data->ray.wall_height / 2);
// 	if (start < 0)
// 		start = 0;
// 	end = (data->window_height / 2) + ((int)data->ray.wall_height / 2);
// 	if (end > data->window_height)
// 		end = data->window_height;
// 	draw_strip(data, id, start, end);
// }

// //----mini map

