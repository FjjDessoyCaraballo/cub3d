/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:51:03 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/08 16:55:17 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static	int8_t	load_pngs(t_data *data)
{
	data->tx_n_wall = mlx_load_png(data->n_sprite);
	data->tx_s_wall = mlx_load_png(data->s_sprite);
	data->tx_e_wall = mlx_load_png(data->e_sprite);
	data->tx_w_wall = mlx_load_png(data->w_sprite);
	if (!data->tx_n_wall || !data->tx_s_wall || !data->tx_e_wall
		|| !data->tx_w_wall)
		return (FAILURE);
	data->im_n_wall = mlx_texture_to_image(data->mlx, data->tx_n_wall);
	data->im_s_wall = mlx_texture_to_image(data->mlx, data->tx_s_wall);
	data->im_e_wall = mlx_texture_to_image(data->mlx, data->tx_e_wall);
	data->im_w_wall = mlx_texture_to_image(data->mlx, data->tx_w_wall);
	if (!data->im_n_wall || !data->im_s_wall || !data->im_e_wall
		|| !data->im_w_wall)
		return (FAILURE);
	return (SUCCESS);
}

uint32_t	load_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int8_t	draw_floor_ceiling(t_data *data)
{
	int			i;
	int			j;

	i = 0;
	if (!data->background)
		return (FAILURE);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(data->background, j, i, load_rgb(data->c_red, \
				data->c_green, data->c_blue, 255));
			else
				mlx_put_pixel(data->background, j, i, load_rgb(data->f_red, \
				data->f_green, data->f_blue, 255));
			j++;
		}
		i++;
	}
	if (mlx_image_to_window(data->mlx, data->background, 0, 0) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	image_initialization(t_data *data)
{
	data->background = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->background == NULL || data->im_ray == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	image_handling(t_data *data)
{
	if (image_initialization(data) == FAILURE)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));	
	if (load_pngs(data) == FAILURE)
		return (err_msg(NULL, MLX2, FAILURE));
	else
		delete_pngs(data);
	if (draw_floor_ceiling(data) == FAILURE)
		return (err_msg(NULL, MLX4, FAILURE));
	return (SUCCESS);
}
