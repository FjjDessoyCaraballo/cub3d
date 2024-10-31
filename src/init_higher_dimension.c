/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/10/31 10:45:23 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Define what colour from the specified pixel should be use next
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
 * does not have enough value for such low graphics
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
 * Find which direction of wall image we need for this ray
 */
int	find_wall(t_data *data, int i)
{
	//printf("word for dir = %f\n", data->ray_hit[i]);
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
/*int	find_wall(t_data *data, int i)
{
	(void)i;
	if (data->ray_hit == NORTH)
		data->im_current_wall = data->im_n_wall;	
	else if (data->ray_hit == SOUTH)
		data->im_current_wall = data->im_s_wall;
	else if (data->ray_hit == EAST)
		data->im_current_wall = data->im_e_wall;
	else if (data->ray_hit == WEST)
		data->im_current_wall = data->im_w_wall;
	if (data->im_current_wall == NULL)
		return (FAILURE);
	return (SUCCESS);
}*/

/*int	draw_wall(t_data *data, int i, int x, double img_y)
{
	double	wall_h;
	double top_of_wall;
	double current_wall_pos;
	double img_x; 
	double img_y_inc;
	uint32_t colour = 0;
	//uint32_t colour2 = 0;
	
	if (find_wall(data, i) == FAILURE)
		return (FAILURE);
	wall_h = HEIGHT / data->ray_len * DIST_TO_PLANE * WALL_SCALE_FACTOR; // we get the height of the wall based on len
	top_of_wall = (HEIGHT - wall_h) / 2; // we set our starting point to the top of where th wall begins
	current_wall_pos = top_of_wall; // we set our incrementer 
	img_x = (double)i / RAY_MAX * data->im_current_wall->width;
	x = i * SEGMENT;
	img_y_inc = (double)data->im_current_wall->height / wall_h;
	while (current_wall_pos < top_of_wall + wall_h)
	{
		if (x >= 0 && x < WIDTH && current_wall_pos > 0 && current_wall_pos < HEIGHT)
		{
			img_y = (current_wall_pos - top_of_wall) / wall_h * data->im_current_wall->height;
			if (x >= 0 && x < WIDTH && data->ray_len > 0)
			{
				if (img_y >= 0 && img_y < data->im_current_wall->height)
				{
					colour = fetch_pixel_rgb(data->im_current_wall, img_x, img_y, 0);
					//colour2 = fetch_pixel_rgb(data->im_ray, x, current_wall_pos, 0);
				}
				// this is a segv protection
				if (colour == 0)// || colour == colour2)
					break ;
				//if ()
				mlx_put_pixel(data->im_ray, x, (int)current_wall_pos, colour);
			}
		}
		current_wall_pos++;
		img_y += img_y_inc;
	}
	return (SUCCESS);
}*/
int	draw_wall(t_data *data, int i, int x, double img_y)
{
	double	wall_h;
	double top_of_wall;
	double current_wall_pos;
	double img_x; 
	double img_y_inc;
	uint32_t colour = 0;
	//double new_len;
	 //double hit_pos;
	if (find_wall(data, i) == FAILURE)
	{
		printf("failure on ray number = %d\n", i);
		return (FAILURE);
	}
	//new_len = data->ray_len[i] * T_SIZE;
	//printf("new len = %f\n", new_len);
	if (data->ray_len[i] <= 0)
		printf("WZOOOOOOOOO\n");
	//wall_h = HEIGHT / new_len;
	//printf("what is wall height = %f\n", wall_h);
	wall_h = HEIGHT / data->ray_len[i] * DIST_TO_PLANE * WALL_SCALE_FACTOR; // we get the height of the wall based on len
	if (wall_h <= 0)
		printf("oho\n");
	top_of_wall = (HEIGHT - wall_h) / 2;// * T_SIZE; // we set our starting point to the top of where th wall begins
	if (top_of_wall <= 0)
		printf("eeeek\n");
	//printf("what is ray_x = %f\n", data->ray_x);
	current_wall_pos = top_of_wall; // we set our incrementer 
	/*if (data->ray_hit[i] == EAST || data->ray_hit[i] == WEST) {
        // Vertical wall, use y-coordinate
        hit_pos = fmod(data->ray_y, 64.0) / 64.0;
        img_x = (int)(hit_pos * data->im_current_wall->width);
    } else {
        // Horizontal wall, use x-coordinate
        hit_pos = fmod(data->ray_x, 64.0) / 64.0;
        img_x = (int)(hit_pos * data->im_current_wall->width);
    }*/
	//img_x = (img_x < 0) ? 0 : (img_x >= data->im_current_wall->width) ? data->im_current_wall->width - 1 : img_x;
	//printf("what si imgx = %u\n", img_x);
	//double hit_position = fmod(data->ray_x, 64.0) / 64.0;
	//printf("hit ps = %f\n", hit_pos);
	//img_x = (uint32_t)hit_position * data->im_current_wall->width + 1;
	//printf("imgx = %u\n", img_x);
	img_x = (double)i / RAY_MAX * data->im_current_wall->width;
	//img_x = data->im_current_wall->width - x / RAY_MAX;
	//if (img_x <= 0)
	//{
	//	img_x = 0.01;//data->ray_len[i];
	//	printf("img x issues = %f at = %d wall_h = %f current img width = %u\n", img_x, i, wall_h, data->im_current_wall->width);//, hit_pos);
	//}
	x = i * SEGMENT;
	img_y_inc = data->im_current_wall->height / wall_h;
    current_wall_pos = top_of_wall;
	//if (current_wall_pos < 0)
	//	printf("current_wall_pos = %f\n", current_wall_pos);
	while (current_wall_pos > 0 && current_wall_pos < top_of_wall + wall_h && current_wall_pos < HEIGHT)
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
					if (colour == 0 || colour == 0x00000000)
					{
						printf("we at ray = %d\n", i);
						printf("Color is 0 at img_x = %f, img_y = %f, current_wall_pos = %f\n", img_x, current_wall_pos, img_y);
						break ;
					}
					mlx_put_pixel(data->im_ray, x, current_wall_pos, colour);
				}
				else
				{
					printf("didnt stick a a pixel on wall on ray = %d\n", i); // does not print anything	
					printf("imgy = %f width img = %u imgx = %f\n", img_y, data->im_current_wall->height, img_x);
				}
			}
		}
		current_wall_pos++;
		if (current_wall_pos <= 0)
			printf("yaar\n");
		//img_y += img_y_inc;
	}
	//printf("wall_h = %f top_of_wall = %f current_wall_pos = %f\n", wall_h, top_of_wall, current_wall_pos);
	return (SUCCESS);
}
			
			/*~~stretchy blocks ~~*/
			//img_y = (current_wall_pos - top_of_wall) * img_y_inc;
			
			/*~~many thin blocks~~*/
			//img_x = (int)((x % T_SIZE) % T_SIZE) % data->im_current_wall->width;
			
			//img_x = (int)((x % T_SIZE) % T_SIZE) % data->im_current_wall->width;
			//printf("whats img x = %f\n", img_x);
			//img_x = (x % data->im_current_wall->width);
				/*~~this was a fun piece of code, try it~~*/
			//img_y = (uint32_t)(current_wall_pos - top_of_wall) % data->im_current_wall->height;  // Tiling the texture vertically
