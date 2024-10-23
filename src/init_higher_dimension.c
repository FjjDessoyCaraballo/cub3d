/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/10/23 16:04:42 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * set up for 3d stuff 
 * 
 */
/*int	init_bigmap(t_data *data)
{
	data->tx_n_wall = mlx_load_png("data->path...wall.png");
	data->tx_s_wall = mlx_load_png("data->path...wall.png");
	data->tx_e_wall = mlx_load_png("data->path...wall.png");
	data->tx_w_wall = mlx_load_png("data->path...wall.png");
	if (data->tx_n_wall == NULL || data->tx_s_wall == NULL 
	|| data->tx_e_wall == NULL || data->tx_w_wall)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_n_wall = mlx_texture_to_image(data->mlx, data->tx_n_wall);
	data->im_s_wall = mlx_texture_to_image(data->mlx, data->tx_s_wall);
	data->im_e_wall = mlx_texture_to_image(data->mlx, data->tx_e_wall);
	data->im_w_wall = mlx_texture_to_image(data->mlx, data->tx_w_wall);
	if (data->im_n_wall == NULL || data->im_s_wall == NULL 
	|| data->im_e_wall == NULL || data->im_w_wall)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	// set floor to data->rgb values
	// set cieling to data->rgb values
}*/
/*char	get_texture(t_data *data)
{
	if (data->hitdir == 1)
		return (data->im_n_wall); ?? dont know what to return
	else if (data->hitdir == 2)
		return (south);
	else if (data->hitdir == 3)
		return ();
	else if (data->hitdir == 4)	
		return ();
}*/
//		get_texture[i];

/*void render_3d_scene(t_data *data) {
    for (int i = 0; i < NUM_RAYS; i++) {
        double ray_length = data->ray_len[i];
        int wall_face = data->hit_face[i];

        double wall_height = SCREEN_data->w_height / ray_length;
        double ceiling = (SCREEN_data->w_height / 2.0) - (wall_height / 2.0);
        double floor = (SCREEN_data->w_height / 2.0) + (wall_height / 2.0);

        draw_wall_slice(data, i, ceiling, floor, wall_face);
    }
}

void draw_wall_slice(t_data *data, int x, double ceiling, double floor, int face) {
    uint32_t* texture = get_texture_for_face(face);
    for (int y = 0; y < SCREEN_data->w_height; y++) {
        if (y < ceiling) {
            // Draw ceiling
            mlx_put_pixel(data->im_screen, x, y, ceiling_color);
        } else if (y > floor) {
            // Draw floor
            mlx_put_pixel(data->im_screen, x, y, floor_color);
        } else {
            // Draw wall with appropriate texture
            int texture_y = (y - ceiling) * TEXTURE_data->w_height / (floor - ceiling);
            mlx_put_pixel(data->im_screen, x, y, texture[texture_y]);
        }
    }
}*/

/**
 * Clears a singular line of pixels so we can re draw ne set of pixels on 
 * a clear canvas, in theory this could only clear pixels that are previouse
 * wall and not new wall, this code was simpler and payoff for workload
 * does not have enough value for such low graphics
 */
static void	clear_img(t_data *data, int i)
{
	int	y;
	int	x;

	y = 0;
	x = i * (data->w_width / RAY_MAX);
	while (y < data->w_height)
	{
		mlx_put_pixel(data->im_ray, x, y, 0x00000000);	
		y++;
	}	
}

static uint32_t rgb(t_data *data, int x, int y, int i)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
	if (data->ray_hit[i] == NORTH)
		data->im_current_wall = data->im_n_wall;	
	else if (data->ray_hit[i] == SOUTH)
		data->im_current_wall = data->im_s_wall;
	else if (data->ray_hit[i] == EAST)
		data->im_current_wall = data->im_e_wall;
	else if (data->ray_hit[i] == WEST)
		data->im_current_wall = data->im_w_wall;
	r = data->im_current_wall->pixels[(y * data->im_current_wall->width + x) * 4]; //4 bytes per pixel
	g = data->im_current_wall->pixels[((y * data->im_current_wall->width + x) * 4) + 1];
	b = data->im_current_wall->pixels[((y * data->im_current_wall->width + x) * 4) + 2];
	a = data->im_current_wall->pixels[((y * data->im_current_wall->width + x) * 4) + 3];
	return (load_rgb(r, g, b, a));
}

/*int	draw_section(t_data *data, double wall_h, double wall_i, int x)
{
	double wall_bottom;
	double img_y;
	double img_y_step;
	double img_x;

	wall_bottom = wall_i + wall_h;
	img_y = 0;
	img_y_step = (double)data->im_n_wall->height / wall_h;
	img_x = (double)x / RAY_MAX * data->im_n_wall->width;
	//x = x * (data->w_width / RAY_MAX);
	while (wall_i < wall_bottom)
	{
		if (wall_i > 0 && wall_i < data->w_height)
		{
			if (x >= 0 && x < data->w_width && data->ray_len[x] > 0)
				mlx_put_pixel(data->im_ray, x * (data->w_width / RAY_MAX), (int)wall_i, rgb(data, img_x, img_y));
		}
//		current_wall_pos += increment;
		wall_i++;
		img_y += img_y_step;
	}	
	return (SUCCESS);
}


int draw_wall(t_data *data, int i, int img_x, int x)
{
	double	wall_h;
	double wall_top;
	//double current_wall_pos;
	//double	img_y_step;
	(void)img_x;
	(void)x;
	//x = i * (data->w_width / RAY_MAX);
	wall_h = data->w_height / data->ray_len[i];
	wall_top = (data->w_height - wall_h) / 2;
	clear_img(data, i);
	draw_section(data, wall_h, wall_top, i);
	return (SUCCESS);
}*/

int	draw_wall(t_data *data, int i, int x, double img_y)
{
	double	wall_h;
	double top_of_wall;
	double current_wall_pos;
	double img_x; 
	double img_y_inc;
	uint32_t colour;
	double distance_to_plane = (data->w_width / 2) / tan(FOV / 2 * PI / 180);
	double wall_scale_factor = 0.01; // or STEP? 

	//printf("check = %f\n", distance_to_plane);
	wall_h = data->w_height / data->ray_len[i] * distance_to_plane * wall_scale_factor; // 8 needs to be a fluctuating number . // we get the height of the wall based on len
	top_of_wall = (data->w_height - wall_h) / 2; // we set our starting point to the top of where thw all begins
	current_wall_pos = top_of_wall; // we set our incrementer 
	img_x = (double)i / RAY_MAX * data->im_n_wall->width;
	x = i * (data->w_width / RAY_MAX);
	img_y_inc = (double)data->im_n_wall->height / wall_h;
	clear_img(data, i);
	while (current_wall_pos < top_of_wall + wall_h)
	{
		if (x >= 0 && x < data->w_width && current_wall_pos > 0 && current_wall_pos < data->w_height)
		{
			if (x >= 0 && x < data->w_width && data->ray_len[i] > 0)
			{
				colour = rgb(data, img_x, img_y, i);
				mlx_put_pixel(data->im_ray, x, (int)current_wall_pos, colour);
			}
		}
		current_wall_pos++;
		img_y += img_y_inc;
	}	
	return (SUCCESS);
}