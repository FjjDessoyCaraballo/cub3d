/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/10/24 10:57:57 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

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
	int pos;
	
	if (data->ray_hit[i] == NORTH)
		data->im_current_wall = data->im_n_wall;	
	else if (data->ray_hit[i] == SOUTH)
		data->im_current_wall = data->im_s_wall;
	else if (data->ray_hit[i] == EAST)
		data->im_current_wall = data->im_e_wall;
	else if (data->ray_hit[i] == WEST)
		data->im_current_wall = data->im_w_wall;
	if (data->im_current_wall != NULL)
	{
		pos = (y * data->im_current_wall->width + x) * 4;
		r = data->im_current_wall->pixels[pos]; //4 bytes per pixel
		g = data->im_current_wall->pixels[pos + 1];
		b = data->im_current_wall->pixels[pos + 2];
		a = data->im_current_wall->pixels[pos + 3];
		return (load_rgb(r, g, b, a));
	}
	return (0);
}

int	draw_wall(t_data *data, int i, int x, double img_y)
{
	double	wall_h;
	double top_of_wall;
	double current_wall_pos;
	double img_x; 
	double img_y_inc;
	uint32_t colour = 0;
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
			img_y = (current_wall_pos - top_of_wall) / wall_h * data->im_n_wall->height;
			if (x >= 0 && x < data->w_width && data->ray_len[i] > 0)
			{
				if (img_y >= 0 && img_y < data->im_n_wall->height)
					colour = rgb(data, img_x, img_y, i);
				// this is a segv protection
				if (colour == 0)
					break ;
				mlx_put_pixel(data->im_ray, x, (int)current_wall_pos, colour);
			}
		}
		current_wall_pos++;
		img_y += img_y_inc;
	}
	return (SUCCESS);
}