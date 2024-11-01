/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 16:50:44 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"



/**
 * Draws a line of predefined size for 2d on large map, this will be copied and 
 * adjusted for 3d. The creation of the first line allows for 
 * update player function, in movement.c to start by deleting an image so we 
 * can redraw the image.
 */
void	wipe_line(t_data *data)
{
	int			i;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	i = 0;
	start_x = data->line_x;
	start_y = data->line_y;
	while (i <= 40)
	{
		draw_x = start_x + (int)(data->p_dir_x * i);
		draw_y = start_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
			mlx_put_pixel(data->im_mini_ray, draw_x, draw_y, 0x00000000);
		i++;
	}
}

void	draw_first_line(t_data *data, int new_x, int new_y)
{
	uint32_t	red;
	int			i;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	red = 0xFF00FFF0;
	i = 0;
	start_x = new_x;
	start_y = new_y;
	while (i <= 40)
	{
		draw_x = start_x + (int)(data->p_dir_x * i);
		draw_y = start_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
		{
			mlx_put_pixel(data->im_mini_ray, draw_x, draw_y, red);
		}
		i++;
	}
}



void	draw_mini_player(t_data *data)
{
	uint32_t	red;
	int			radius;
	double		center_x;
	double		center_y;
	int			y = 0;
	int			x = 0;
	int			draw_x;
	int			draw_y;
	int p_x = (int)data->x_ppos;
	int p_y = (int)data->y_ppos;
	
	red = 0xFF0000FF;
	radius = MINI_T / 4;
	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	center_x = (p_x / MINI_T) + MINI_T / 2;
    center_y = (p_y / MINI_T) + MINI_T / 2;
	y = -radius;
	data->line_x = center_x;
	data->line_y = center_y;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x) + (y * y) <= (radius * radius))
			{
				draw_x = center_x + x;
				draw_y = center_y + y;
				if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
					mlx_put_pixel(data->im_map_player, draw_x, draw_y, red);
			}
			x++;
		}
		y++;
	}
	//data->line_x = draw_x;
	//data->line_y = draw_y;
}

//#include <string.h> //~~ testing 
/*~~ the purpose of this function is to attempt to rotate a player texture
1. the image rotates around its center axis 
2. it should do it so that the image remains intact, unfortunatley there is heavy distortion
3. this is to be fixed only if we have time or interest 
~~*/
