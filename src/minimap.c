/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 17:10:14 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"



void make_minimap_transparent(mlx_image_t *image, float transparency)
{
	uint32_t y = 0;
	uint32_t x = 0;
	uint32_t *pixel;
    while (y < image->height)
	{
        while (x < image->width)
		{
            pixel = (uint32_t *)(image->pixels + (y * image->width + x) * sizeof(uint32_t));
            
            // Extract RGBA components
            uint8_t r = (*pixel >> 24) & 0xF0;
            uint8_t g = (*pixel >> 16) & 0xF0;
            uint8_t b = (*pixel >> 8) & 0xF0;
            uint8_t a = (*pixel) & 0xF0;

            // Adjust the alpha channel
            a = (uint8_t)(a * transparency);
            
            // Recompose the pixel with the new alpha value
            *pixel = (r << 24) | (g << 16) | (b << 8) | a;
			x++;
        }
		x = 0;
		y++;
    }
}
/**
 * Inits mini texture to mini image and resizes
 */
int	init_mini_imgs(t_data *data)
{	
	data->tx_mini_floor = mlx_load_png("./minimap_textures/floor.png");
	data->tx_mini_wall = mlx_load_png("./minimap_textures/grass.png");
	if (data->tx_mini_floor == NULL || data->tx_mini_wall == NULL)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_mini_floor = mlx_texture_to_image(data->mlx, data->tx_mini_floor);
	data->im_mini_wall = mlx_texture_to_image(data->mlx, data->tx_mini_wall);
	if (data->im_mini_floor == NULL || data->im_mini_wall == NULL)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	if (mlx_resize_image(data->im_mini_floor, MINI_T, MINI_T) == false)
		return (err_msg(NULL, RESIZE, FAILURE));
	if (mlx_resize_image(data->im_mini_wall, MINI_T, MINI_T) == false)
		return (err_msg(NULL, RESIZE, FAILURE));
	return (SUCCESS);
}

/**
 * Create an image and fill each tile with both floor and wall
 * instances will be utilized in draw minimap to switch images on and off.
 */
/*void draw_mini_wall(t_data *data, int x, int y, uint32_t colour)
{

	for (int j = 0; j < MINI_T; j++) {
        for (int i = 0; i < MINI_T; i++) {
            mlx_put_pixel(data->im_map, x + i, y + j, colour); // Replace WALL_COLOR with actual color
        }
    }
}*/

void draw_mini_tile(t_data *data, int x, int y, u_int32_t colour)
{
	int j = 0;
	int i = 0;
	
    while (j < MINI_T)
	{
		
        while (i < MINI_T)
		{
            mlx_put_pixel(data->im_map, x + i, y + j, colour); // Replace FLOOR_COLOR with actual color
	    	i++;
	    }
		i = 0;
	    j++;
	}
}

int	init_map(t_data *data)
{
	int	x;
	int	y;
	uint32_t colour;
    
	colour = 0;
	x = 0;
	y = 0;
	data->im_map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_map == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	while (y < data->map_length)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
			{
				colour = fetch_pixel_rgb(data->im_mini_wall, x, y, 0);
				draw_mini_tile(data, x * MINI_T, y * MINI_T, colour);
			}
			else if (data->map[y][x] == '0')
			{
				colour = fetch_pixel_rgb(data->im_mini_floor, x, y, 0);
				draw_mini_tile(data, x * MINI_T, y * MINI_T, colour);
			}
			x++;
		}
		x = 0;
		y++;
	}
	make_minimap_transparent(data->im_map, 0.9f);
	return (SUCCESS);
}

///original below
/*int	init_map(t_data *data)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	data->im_map = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	if (data->im_map == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	while (y < 7)
	{
		while (x < 7)
		{
			if (mlx_image_to_window(data->mlx, data->im_mini_floor, x * MINI_T, y * MINI_T) == -1)
				return (err_msg(NULL, IMG_TO_WIN, FAILURE));
			if (mlx_image_to_window(data->mlx, data->im_mini_wall, x * MINI_T, y * MINI_T) == -1)
				return (err_msg(NULL, IMG_TO_WIN, FAILURE));
			x++;
		}
		x = 0;
		y++;
	}	
	//if (mlx_image_to_window(data->mlx, data->im_map, MINI_WIDTH, MINI_HEIGHT) == -1)
	//	return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	return (SUCCESS);
}*/


//adjust_tilesize(data); maybe
int	initlize_minimap(t_data *data)
{
	//printf("pos x = %f, pops y = %f\n", data->x_ppos - 0.5, data->y_ppos);
	if (init_mini_imgs(data) == FAILURE)
		return (err_msg(NULL, MLX1, FAILURE));
	data->im_map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (init_map(data) == FAILURE)
		return (FAILURE);
	
//	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	draw_mini_player(data);
	data->im_mini_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_first_line(data, data->line_x, data->line_y);
	return (SUCCESS);
}


/* here lies a thoughst graveyard */

/*
this fucntion may not be needed, it readjust the tile size (pixels)
based on screen width and height, should we want to make sure everything fits
no matter the size of the map, up untill the pixels become too small for a 
visually functioning game.
*/
/* 
int adjust_tilesize(t_data *data)
{
	size_t	x_comp;
	size_t	y_comp;
	if (data->map_width * data->t_size > WIDTH || data->map_length * data->t_size > HEIGHT)
	{
		x_comp = data->map_width * data->t_size;
		y_comp = data->map_length * data->t_size;
		if (x_comp > y_comp && x_comp > WIDTH)
		{
			while (data->map_width * data->t_size > WIDTH)
			{
				data->t_size -= 1;
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
		else if (data->map_length * data->t_size > HEIGHT)
		{
			while (data->map_length * data->t_size > HEIGHT)
			{
				data->t_size -= 1;	
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
	}
	return (0);
}*/
/**
 * This draws a red circle as a player marker on the screen.
 * It is utilized right now just to visualize a 2d perspective where the 
 * 3d perspective will go, can be removed once the minimap is complete , will be switched
 * off when the 3d starts to get rendered.
 * no return vallue as its for testing right now
 */
/*void	draw_player(t_data *data)
{
	uint32_t	red;
	int			radius;
	int			center_x;
	int			center_y;
	int			y;
	int			x;
	int			draw_x;
	int			draw_y;

	red = 0xFF0000FF;
	radius = 20 / 2;
	data->im_mini_player = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	center_x = (int)(data->x_ppos * T_SIZE) + T_SIZE / 2;
	center_y = (int)(data->y_ppos * T_SIZE) + T_SIZE / 2;
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
				if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
					mlx_put_pixel(data->im_mini_player, draw_x, draw_y, red);
			}
			x++;
		}
		y++;
	}
}*/

