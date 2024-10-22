/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/10/22 10:34:29 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"



/**
 * This fucntion is soon to become oboslete as almost all
 * data has been collected by parsing, still missing dir_x and y
 * 
 */
void	init_mini_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	//~~ char p = loop through bool to find which one is true, return char.
	//data->im_mini_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	//if (data->im_mini_player == NULL)
	//	return;// (FAILURE);
	while (y < data->map_length)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x])
			{
				if (data->map[y][x] == 'N' && x < data->map_width && y < data->map_length) // N ret char
				{
				// reps north right now .
					data->p_dir_x = 0;
					data->p_dir_y = -1;
					//if (data->ray_size == 0)
					//	data->ray_size = 40;
					data->map[y][x] = '0'; // we dont need the n anymore
					//draw_first_line(data);
	//				mlx_image_to_window(data->mlx, data->im_mini_player, 0, 0);
				}
			}
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
	if (mlx_image_to_window(data->mlx, data->im_map, MINI_WIDTH, MINI_HEIGHT) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
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
	//data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	//mlx_image_to_window(data->mlx, data->im_ray, WIDTH, HEIGHT);
//	stack_ray_data(data, 0);
//	mlx_image_to_window(data->mlx, data->im_ray, WIDTH, HEIGHT);
	//if (init_mini_imgs(data) == FAILURE)
	//	return (FAILURE);
	//if (init_map(data) == FAILURE)
	//	return (FAILURE);
	
	init_mini_player(data);
	
	//draw_mini_map(data, 0, 0 , 0);	
	//draw_mini_player(data);

	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_ray == NULL)
		printf("null on init or ray img\n");
	//mlx_image_to_window(data->mlx, data->im_ray, WIDTH, HEIGHT);	
	//mlx_delete_image(data->mlx, data->im_map_player);
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

