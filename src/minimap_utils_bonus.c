/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/11/05 13:49:36 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * null checking can be moved elsewhere
 */

int img_to_win(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->im_ray, 0, 0) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	if (mlx_image_to_window(data->mlx, data->im_map, 0, 0) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	if (mlx_image_to_window(data->mlx, data->im_map_player, 0, 0) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	if (mlx_image_to_window(data->mlx, data->im_mini_ray,  0, 0) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	return (SUCCESS);
}
/**
 * We finalize the scenery by putting images to window , adjusting the mini player 
 * and setting the layering depths of the images so they all display correctly.
 */
int	set_view(t_data * data)
{
	if (img_to_win(data) == FAILURE)
		return (FAILURE);
	data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_map_player->instances[0].y = (data->y_ppos - 0.5) * MINI_T;	
	mlx_set_instance_depth(data->im_ray->instances, 1);
	mlx_set_instance_depth(data->im_map->instances, 2);
	mlx_set_instance_depth(data->im_map_player->instances, 3);	
	mlx_set_instance_depth(data->im_mini_ray->instances, 4);
	//errr??
	data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * MINI_T;	
	return (0); //success
}

void	wipe_line(t_data *data, int new_x, int new_y)
{
	int			i;
	int			draw_x;
	int			draw_y;

	i = 0;
	new_x = ((int)data->x_ppos / MINI_T) + MINI_T / 2;
  	new_y = ((int)data->y_ppos / MINI_T) + MINI_T / 2;
	while (i <= 40)
	{
		draw_x = new_x + (int)(data->p_dir_x * i);
		draw_y = new_y + (int)(data->p_dir_y * i);
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


void	draw_mini_line(t_data *data, int new_x, int new_y)
{
	int			i;
	int			draw_x;
	int			draw_y;

	i = 0;
	new_x = ((int)data->x_ppos / MINI_T) + MINI_T / 2;
    new_y = ((int)data->y_ppos / MINI_T) + MINI_T / 2;
	while (i <= 40)
	{
		draw_x = new_x + (int)(data->p_dir_x * i);
		draw_y = new_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < MINI_WIDTH && draw_y >= 0 && draw_y < MINI_HEIGHT)
			mlx_put_pixel(data->im_mini_ray, draw_x, draw_y, RED);
		i++;
	}
}


void	draw_mini_player(t_data *data, int y, int x)
{
	double		center_x;
	double		center_y;
	int			draw_x;
	int			draw_y;
	
	center_x = ((int)data->x_ppos / MINI_T) + MINI_T / 2;
    center_y = ((int)data->y_ppos/ MINI_T) + MINI_T / 2;
	y = -M_RADIUS;
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
