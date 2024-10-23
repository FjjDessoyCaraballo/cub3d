/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/10/23 16:11:51 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Takes player position and adjusts it based on minimapp size, minimap
 * consists of 6 x 6 tiles. This assumes we want player in center of minimap.
 * @param p_x x_ppos type cast to int
 * @param p_y y_ppos type cast to int
 * int type casting may be oboslete depending on decision of minimap handeling
 */
void	adjust_mapstart(int *p_x, int *p_y)
{
	if (*p_x >= 3)
		(*p_x) -= 3;
	else if (*p_x == 2)
		(*p_x) -= 2;
	else if (*p_x == 1)
		(*p_x) -= 1;
	if (*p_y >= 3)
		(*p_y) -= 3;
	else if (*p_y == 2)
		(*p_y) -= 2;
	else if (*p_y == 1)
		(*p_y) -= 1;
}

/**
 * Draws a line of predefined size for 2d on large map, this will be copied and 
 * adjusted for 3d. The creation of the first line allows for 
 * update player function, in movement.c to start by deleting an image so we 
 * can redraw the image.
 */

void	draw_first_line(t_data *data)
{
	uint32_t	red;
	int			i;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	red = 0xFF00FFF0;
	i = 0;
	start_x = (data->x_ppos * T_SIZE) + T_SIZE / 2;
	start_y = (data->y_ppos * T_SIZE) + T_SIZE / 2;
	data->im_ray = mlx_new_image(data->mlx, data->w_width, data->w_height);
	// if north draw up so -y
	while (i <= 40)
	{
		draw_x = start_x + (int)(data->p_dir_x * i);
		draw_y = start_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < data->w_width && draw_y >= 0 && draw_y < data->w_height)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		i++;
	}
    mlx_image_to_window(data->mlx, data->im_ray, data->w_width, data->w_height); // 0, 0
}

/**
 * This function gets called in movement.c for drawing each ray for visual aid
 * Will be copied and adjusted for 3d perspective.
 * We do not handle facing different directions yet this will be added with simple
 * if statment or collected information in parsing will set data->ray_dir*
 * to correct directin
 */
void	draw_line(t_data *data, int i)
{
	uint32_t	red;
	int			len;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	len = 0;
	red = 0xFF00FFF0;
	start_x = (data->x_ppos * T_SIZE) + T_SIZE / 2;
	start_y = (data->y_ppos * T_SIZE) + T_SIZE / 2;
	// if north draw up so -y
	while (len <= data->ray_len[i])
	{
		draw_x = start_x + (int)(data->ray_dir_x * len);
		draw_y = start_y + (int)(data->ray_dir_y * len);
		if (draw_x >= 0 && draw_x < data->w_width && draw_y >= 0 && draw_y < data->w_height)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		len++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, data->w_width, data->w_height); // 00
}
	//if south draw like this
	/*while (i <= ray_size)
	{
		printf("bug hunting 2\n");
		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		int draw_x = start_x; // + i
		int draw_y = start_y + i; // + x
		if (draw_x >= 0 && draw_x < data->w_width && draw_y >= 0 && draw_y < data->w_height)
		{
			printf("draw x = %d\n", draw_x);
			printf("draw y = %d\n", draw_y);
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
			printf("the xxx = %d\n", x);
			printf("bug hunting 3\n");
		}
		x++;
		printf("bug hunting 4\n");	
		i++;
	}*/

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
	
	//adjust_mapstart(&p_x, &p_y);
	red = 0xFF0000FF;
	radius = MINI_T / 4; // 6
	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	center_x = (p_x / MINI_T) + MINI_T / 2;
    center_y = (p_y / MINI_T) + MINI_T / 2;
	y = -radius;
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
	//data->im_ray = mlx_new_image(data->mlx, data->w_width, data->w_height);
	//mlx_put_pixel(data->im_ray, 1, 1, red);
	//mlx_image_to_window(data->mlx, data->im_ray, MINI_data->w_width, MINI_data->w_height);
	mlx_image_to_window(data->mlx, data->im_map_player, MINI_WIDTH, MINI_HEIGHT);
//	mlx_image_to_window(data->mlx, data->im_ray, data->w_width, data->w_height);
}

//#include <string.h> //~~ testing 
/*~~ the purpose of this function is to attempt to rotate a player texture
1. the image rotates around its center axis 
2. it should do it so that the image remains intact, unfortunatley there is heavy distortion
3. this is to be fixed only if we have time or interest 
~~*/
