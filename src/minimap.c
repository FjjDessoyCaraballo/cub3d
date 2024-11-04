/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/11/04 14:23:16 by fdessoy-         ###   ########.fr       */
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
	mlx_delete_texture(data->tx_mini_floor);
	mlx_delete_texture(data->tx_mini_wall);
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
			if (mlx_image_to_window(data->mlx, data->im_mini_floor, x * \
				MINI_T, y * MINI_T) == -1)
				return (err_msg(NULL, IMG_TO_WIN, FAILURE));
			if (mlx_image_to_window(data->mlx, data->im_mini_wall, x * \
				MINI_T, y * MINI_T) == -1)
				return (err_msg(NULL, IMG_TO_WIN, FAILURE));
			x++;
		}
		x = 0;
		y++;
	}
	return (SUCCESS);
}

/**
 * Under construction , switching of isntances of images based
 * on player position translated to minimap sizes.
 */
void	draw_mini_map(t_data *data, int x, int y, int index)
{
	int	p_x;
	int	p_y;

	p_x = (int)data->x_ppos;
	p_y = (int)data->y_ppos;
	adjust_mapstart(&p_x, &p_y);
	while (y < 7 && ++y)
	{
		while (x < 7 && ++x)
		{
			if ((p_y + y) >= data->map_length || (p_x + x) >= data->map_width)
				break ;
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

int	initlize_minimap(t_data *data)
{
	if (init_mini_imgs(data) == FAILURE)
		return (err_msg(NULL, MLX1, FAILURE));
	if (init_map(data) == FAILURE)
		return (FAILURE);
	draw_mini_player(data);
	return (SUCCESS);
}
