/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/11/06 14:59:10 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Turns things transparent
 */

void	make_transparent(mlx_image_t *im, uint32_t y, uint32_t x, uint32_t *pix)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	while (y < im->height)
	{
		while (x < im->width)
		{
			pix = (uint32_t *)(im->pixels + (y * im->width + x) * sizeof(uint32_t));
			r = (*pix >> 16) & 0xF0;
			g = (*pix >> 8) & 0xF0;
			b = (*pix) & 0xF0;
			a = (*pix >> 24) & 0xF0;
			a = (uint8_t)(a * 0.6f);
			*pix = ((uint32_t)a << 24) | (r << 16) | (g << 8) | b;
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
	data->im_map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	data->im_mini_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_map == NULL || data->im_map_player == NULL
		|| data->im_mini_ray == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	return (SUCCESS);
}

/**
 * Create an image and fill each tile with both floor and wall
 * instances will be utilized in draw minimap to switch images on and off.
 */

void	draw_mini_tile(t_data *data, int x, int y, uint32_t colour)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < MINI_T)
	{
		while (i < MINI_T)
		{
			mlx_put_pixel(data->im_map, x + i, y + j, colour);
			i++;
		}
		i = 0;
		j++;
	}
}

int	init_map(t_data *data, int x, int y, uint32_t colour)
{
	colour = 0;
	x = 0;
	y = 0;
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
	make_transparent(data->im_map, 0, 0, 0);
	return (SUCCESS);
}

int	initlize_minimap(t_data *data)
{
	if (init_mini_imgs(data) == FAILURE)
		return (err_msg(NULL, MLX1, FAILURE));
	if (init_map(data, 0, 0, 0) == FAILURE)
		return (FAILURE);
	draw_mini_player(data, 0, 0);
	draw_mini_line(data, 0, 0);
	set_view(data);
	return (SUCCESS);
}
