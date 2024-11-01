/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 10:11:15 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Find the colour from the textures specified pixel should be drawn next
 */
static uint32_t fetch_pixel_rgb(mlx_image_t *img, int x, int y, int pos)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
	
	if (img != NULL)
	{
		pos = (y * img->width + x) * 4;
		r = img->pixels[pos]; //4 bytes per pixel
		g = img->pixels[pos + 1];
		b = img->pixels[pos + 2];
		a = img->pixels[pos + 3];
		return (load_rgb(r, g, b, a));
	}
	return (0);
}

/**
 * Clears a singular line of pixels so we can re draw ne set of pixels on 
 * a clear canvas, in theory this could only clear pixels that are previouse
 * wall and not new wall, this code was simpler and payoff for workload
 * does not have enough value for such low graphics, keep for testing just incase
 */
/*static void	clear_img(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		//if (fetch_pixel_rgb(data->im_ray, x, y, 0) != 0x00000000)
		//printf("looky here = %d\n", data->im_ray->context);
		mlx_put_pixel(data->im_ray, x, y, 0x00000000);	
		y++;
	}	
}*/

/**
 * Find which wall texture to draw based on direction
 */
int	find_wall(t_data *data, int i)
{
	if (data->ray_hit[i] == NORTH)
		data->im_current_wall = data->im_n_wall;	
	else if (data->ray_hit[i] == SOUTH)
		data->im_current_wall = data->im_s_wall;
	else if (data->ray_hit[i] == EAST)
		data->im_current_wall = data->im_e_wall;
	else if (data->ray_hit[i] == WEST)
		data->im_current_wall = data->im_w_wall;
	if (data->im_current_wall == NULL)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * Takes the ray length and calulate the height of the wall and draws the wall
 * one pixel at a time. Each pixel is chosen from a texture provided and calculated 
 * to fit the 3d world.
 */
int	draw_wall(t_data *data, int i, int x, double img_y)
{
	double	wall_h;
	double top_of_wall;
	double current_wall_pos;
	double img_x; 
	double img_y_inc;
	double max_wall_h;
	uint32_t colour = 0;
	if (find_wall(data, i) == FAILURE)
	{
		printf("failure on ray number = %d\n", i);
		return (FAILURE);
	}
	x = i * SEGMENT;
	img_x = (double)i / RAY_MAX * data->im_current_wall->width;
	wall_h = HEIGHT / data->ray_len[i] * WALL_SCALE;//DIST_TO_PLANE * WALL_SCALE_FACTOR; // we get the height of the wall based on len
/**
 * if wall_h > hscreen height we set wall_h to be 1 less than HEIGTH so we enter the drawing loop
 * this small if loop is supposed to speed things up when turning around close to a wall, it dosnt but 
 * it could be possible to make iit work better.
 */
	if (wall_h > HEIGHT)
	{
		wall_h = HEIGHT - 1;
		img_y_inc = data->im_current_wall->height / wall_h;
		current_wall_pos = 0;
		while (current_wall_pos < HEIGHT)
		{
			img_y = current_wall_pos * img_y_inc;
			colour = fetch_pixel_rgb(data->im_current_wall, img_x, img_y, 0);
			 // Protection against segmentation faults
			if (colour != 0)
			{
				mlx_put_pixel(data->im_ray, x, current_wall_pos, colour);
			}
			current_wall_pos++;
		}
		return (SUCCESS);
	}
	top_of_wall = (HEIGHT - wall_h) / 2;; // we set our starting point to the top of where th wall begins
	current_wall_pos = top_of_wall; // we set our incrementer 
	img_x = (double)i / RAY_MAX * data->im_current_wall->width;
	img_y_inc = data->im_current_wall->height / wall_h;
    current_wall_pos = top_of_wall;
	max_wall_h = top_of_wall + wall_h;
	while (current_wall_pos > 0 && current_wall_pos < max_wall_h && current_wall_pos < HEIGHT)
	{
		if (x >= 0 && x <= WIDTH && current_wall_pos > 0 && current_wall_pos <= HEIGHT)
		{
			//img_y = fmod((current_wall_pos - top_of_wall) * img_y_inc, data->im_current_wall->height); //tiling?
			img_y = (current_wall_pos - top_of_wall) * img_y_inc;
			if (x >= 0 && x < WIDTH && data->ray_len[i] > 0 && current_wall_pos > 0)
			{
				if (img_y >= 0 && img_y <= data->im_current_wall->height && current_wall_pos > 0)
				{
					colour = fetch_pixel_rgb(data->im_current_wall, img_x, img_y, 0);
				// this is a segv protection
					if (colour == 0)
						break ;
					mlx_put_pixel(data->im_ray, x, current_wall_pos, colour);
				}
			}
		}
		current_wall_pos++;
	}
	return (SUCCESS);
}
			
/*~~stretchy blocks ~~*/
//img_y = (current_wall_pos - top_of_wall) * img_y_inc;		
/*~~many thin blocks~~*/
//img_x = (int)((x % T_SIZE) % T_SIZE) % data->im_current_wall->width;
//img_x = (int)((x % T_SIZE) % T_SIZE) % data->im_current_wall->width;
//img_x = (x % data->im_current_wall->width);
/*~~this was a fun piece of code, try it~~*/
//img_y = (uint32_t)(current_wall_pos - top_of_wall) % data->im_current_wall->height;  // Tiling the texture vertically
