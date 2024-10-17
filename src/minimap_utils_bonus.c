/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/10/17 12:39:09 by araveala         ###   ########.fr       */
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
	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// if north draw up so -y
	while (i <= 40)
	{
		draw_x = start_x + (int)(data->p_dir_x * i);
		draw_y = start_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		i++;
	}
    //mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
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
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		len++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
}
	//if south draw like this
	/*while (i <= ray_size)
	{
		printf("bug hunting 2\n");
		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		int draw_x = start_x; // + i
		int draw_y = start_y + i; // + x
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
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
	double			center_y;
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
	//center_x -= (MINI_WIDTH - MINI_T * 6);/// 2;
    //center_y -= (MINI_HEIGHT - MINI_T * 6);// / 2;
	//printf("whats centered = %d and y = %d\n", center_x, center_y);
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
	mlx_image_to_window(data->mlx, data->im_map_player, MINI_WIDTH, MINI_HEIGHT);
}

//#include <string.h> //~~ testing 
/*~~ the purpose of this function is to attempt to rotate a player texture
1. the image rotates around its center axis 
2. it should do it so that the image remains intact, unfortunatley there is heavy distortion
3. this is to be fixed only if we have time or interest 
~~*/
/*
int rotate_player_marker(t_data *data)
{
    int width = T_SIZE;
    int height = T_SIZE;
    mlx_image_t *rotated_image = mlx_new_image(data->mlx, width, height);
    uint8_t *rotated_pixels = ( uint8_t*)rotated_image->pixels;

    double cos_angle = cos(ROTATE_ANGLE);
    double sin_angle = sin(ROTATE_ANGLE);
    int y = 0;
    int x = 0;
    int new_x = 0;
    int new_y = 0;
    int center_x = width / 2;
    int center_y = height / 2;
    // trying to clear the prev pixels but no worky
    memset(rotated_pixels, 0, width * height * 4);
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            //printf("show me x = %d\n", x);
            int src_x = x - center_x;
            int src_y = y - center_y;
            new_x = (int)(cos_angle * src_x - sin_angle * src_y + center_x);
            new_y = (int)(sin_angle * src_x + cos_angle * src_y + center_y);
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
            {
                int x1 = (int)new_x;
                int y1 = (int)new_y;
                int x2 = x1 + 1;
                int y2 = y1 + 1;

                if (x2 >= width) x2 = width - 1;
                if (y2 >= height) y2 = height - 1;

                double a = new_x - x1;
                double b = new_y - y1;

                for (int c = 0; c < 4; c++) // For each color channel (RGBA)
                {
                    rotated_pixels[(y * width + x) * 4 + c] =
                        (1 - a) * (1 - b) * data->im_mini_player->pixels[(y1 * width + x1) * 4 + c] +
                        a * (1 - b) * data->im_mini_player->pixels[(y1 * width + x2) * 4 + c] +
                        (1 - a) * b * data->im_mini_player->pixels[(y2 * width + x1) * 4 + c] +
                        a * b * data->im_mini_player->pixels[(y2 * width + x2) * 4 + c];
                }
                //int src_index = (y * width + x) * 4; // Assuming 4 bytes per pixel (RGBA)
                //int dest_index = (new_y * width + new_x) * 4;
                // rotate original image
                //rotated_pixels[dest_index] = data->im_mini_player->pixels[src_index];
                //rotated_pixels[dest_index + 1] = data->im_mini_player->pixels[src_index + 1];
                //rotated_pixels[dest_index + 2] = data->im_mini_player->pixels[src_index + 2];
                //rotated_pixels[dest_index + 3] = data->im_mini_player->pixels[src_index + 3];
               // rotated_pixels[dest_index + 4] = data->im_mini_player->pixels[src_index + 4];
                // definatley getting somewhere playng around with these , u have 1 hour in the morning to figure it out!
                //rotated_pixels[dest_index + 5] = data->im_mini_player->pixels[src_index + 5];
                //rotated_pixels[dest_index + 6] = data->im_mini_player->pixels[src_index + 6];
                //rotated_pixels[dest_index + 7] = data->im_mini_player->pixels[src_index + 7];
                //printf("roatting ?\n");
            }
            x++;
        }
        y++;
    }
    mlx_image_to_window(data->mlx, rotated_image, data->x_ppos * T_SIZE, data->y_ppos * T_SIZE);
    mlx_delete_image(data->mlx, data->im_mini_player); // Clean up the old image
    data->im_mini_player = rotated_image; // Update the image refer
    return (0);
}*/