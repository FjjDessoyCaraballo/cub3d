/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 17:24:45 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	wipe_line(t_data *data)
{
	int			i;
	int			draw_x;
	int			draw_y;

	i = 0;
	while (i <= 40)
	{
		draw_x = data->line_x + (int)(data->p_dir_x * i);
		draw_y = data->line_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
			mlx_put_pixel(data->im_mini_ray, draw_x, draw_y, 0x00000000);
		i++;
	}
}

/**
 * Draws a line of predefined size for 2d on large map, this will be copied and 
 * adjusted for 3d. The creation of the first line allows for 
 * update player function, in movement.c to start by deleting an image so we 
 * can redraw the image.
 */
void	draw_first_line(t_data *data, int new_x, int new_y)
{
	int			i;
	int			draw_x;
	int			draw_y;

	i = 0;
	while (i <= 40)
	{
		draw_x = new_x + (int)(data->p_dir_x * i);
		draw_y = new_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
		{
			mlx_put_pixel(data->im_mini_ray, draw_x, draw_y, RED);
		}
		i++;
	}
}



void	draw_mini_player(t_data *data, int y, int x)
{
	double		center_x;
	double		center_y;
	int			draw_x;
	int			draw_y;
	
	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	center_x = ((int)data->x_ppos / MINI_T) + MINI_T / 2;
    center_y = ((int)data->y_ppos/ MINI_T) + MINI_T / 2;
	y = -M_RADIUS;
	data->line_x = center_x;
	data->line_y = center_y;
	while (y <= M_RADIUS)
	{
		x = -M_RADIUS;
		while (x <= M_RADIUS)
		{
			if ((x * x) + (y * y) <= (M_RADIUS_M))
			{
				draw_x = center_x + x;
				draw_y = center_y + y;
				if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
					mlx_put_pixel(data->im_map_player, draw_x, draw_y, RED);
			}
			x++;
		}
		y++;
	}
}
