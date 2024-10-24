/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/10/23 16:10:13 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"




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
int	init_map(t_data *data)
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
	//if (mlx_image_to_window(data->mlx, data->im_map, MINI_WIDTH, MINI_data->w_height) == -1)
	//	return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	return (SUCCESS);
}

/**
 * Under construction , switching of isntances of images based
 * on player position translated to minimap sizes.
 */
void	draw_mini_map(t_data *data, int x, int y, int index)
{
	int p_x;
	int p_y;

	p_x = (int)data->x_ppos;
	p_y = (int)data->y_ppos;
	adjust_mapstart(&p_x, &p_y);
	while (y < 7 && ++y)
	{
		while (x < 7 && ++x)
		{
	        if ((p_y + y) >= data->map_length || (p_x + x) >= data->map_width)
			{
				//data->im_mini_wall->instances[index].enabled = 1;
				//data->im_mini_floor->instances[index].enabled = 0;
				break ;
			}
			
			else if (data->map[p_y + y][p_x + x] == '1')
			{
				data->im_mini_wall->instances[index].enabled = 1;
				data->im_mini_floor->instances[index].enabled = 0;
			}
			else if (data->map[p_y + y][p_x + x] == '0')
			{
				data->im_mini_wall->instances[index].enabled = 0;
				data->im_mini_floor->instances[index].enabled = 1;
			}
			index++;
        }
		x = 0;
	}
}

//adjust_tilesize(data); maybe
int	initlize_minimap(t_data *data)
{
	if (init_mini_imgs(data) == FAILURE)
		return (err_msg(NULL, MLX1, FAILURE));
	if (init_map(data) == FAILURE)
		return (FAILURE);
	draw_mini_player(data);
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
	if (data->map_width * data->t_size > data->w_width || data->map_length * data->t_size > data->w_height)
	{
		x_comp = data->map_width * data->t_size;
		y_comp = data->map_length * data->t_size;
		if (x_comp > y_comp && x_comp > data->w_width)
		{
			while (data->map_width * data->t_size > data->w_width)
			{
				data->t_size -= 1;
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
		else if (data->map_length * data->t_size > data->w_height)
		{
			while (data->map_length * data->t_size > data->w_height)
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
	data->im_mini_player = mlx_new_image(data->mlx, data->w_width, data->w_height);
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
				if (draw_x >= 0 && draw_x < data->w_width && draw_y >= 0 && draw_y < data->w_height)
					mlx_put_pixel(data->im_mini_player, draw_x, draw_y, red);
			}
			x++;
		}
		y++;
	}
}*/

