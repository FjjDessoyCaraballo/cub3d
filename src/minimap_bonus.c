/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/11/15 14:14:13 by araveala         ###   ########.fr       */
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
			pix = (uint32_t *)(im->pixels + (y * im->width + x) \
			* sizeof(uint32_t));
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
 * Create an image and fill each tile with both floor and wall
 * instances will be utilized in draw minimap to switch images on and off.
 */

void	draw_mini_tile(t_data *data, int x, int y, uint32_t colour)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < data->mini_t)
	{
		while (i < data->mini_t)
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
	(void)colour;
	while (y < data->map_length)
	{
		while (x < (int)ft_strlen(data->map[y]))
		{
			if (y == data->dpos_y && x == data->dpos_x)
				draw_mini_tile(data, x * data->mini_t, y * data->mini_t, RED);
			else if (data->map[y][x] == '1')
				draw_mini_tile(data, x * data->mini_t, y * data->mini_t, GREEN);
			else if (data->map[y][x] == '0')
				draw_mini_tile(data, x * data->mini_t, y * data->mini_t, GREY);
			x++;
		}
		x = 0;
		y++;
	}
	make_transparent(data->im_map, 0, 0, 0);
	return (SUCCESS);
}

static int	tile_size(t_data *d)
{
	size_t	x_comp;
	size_t	y_comp;

	x_comp = d->map_width * d->mini_t;
	y_comp = d->map_length * d->mini_t;
	if (x_comp > y_comp && x_comp > WIDTH)
	{
		while (d->map_width * d->mini_t > WIDTH)
		{
			d->mini_t -= 1;
			if (d->mini_t < 11)
				err_msg(NULL, BONUS2, FAILURE);
		}
	}
	else if (d->map_length * d->mini_t > HEIGHT)
	{
		while (d->map_length * d->mini_t > HEIGHT)
		{
			d->mini_t -= 1;
			if (d->mini_t < 11)
				err_msg(NULL, BONUS2, FAILURE);
		}
	}
	return (SUCCESS);
}

int	initialize_minimap(t_data *data)
{
	data->mini_t = MINI_T;
	if (data->map_length * MINI_T > HEIGHT || data->map_width * MINI_T > WIDTH)
	{
		if (tile_size(data) == FAILURE)
			return (FAILURE);
	}
	data->im_map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_map_player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	data->im_mini_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_map == NULL || data->im_map_player == NULL
		|| data->im_mini_ray == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	if (init_map(data, 0, 0, 0) == FAILURE)
		return (FAILURE);
	draw_mini_player(data, 0, 0);
	draw_mini_line(data, 0, 0);
	set_view(data);
	return (SUCCESS);
}
