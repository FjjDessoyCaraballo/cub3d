/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:51:03 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/21 11:06:41 by fdessoy-         ###   ########.fr       */
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

static int8_t	load_rgb(t_data *data)
{
	data->ceiling_color = (data->c_red << 24) |(data->c_green << 24) \
	| (data->c_blue << 24);
	data->floor_color = (data->f_red << 24) | (data->f_green << 24) \
	| (data->f_blue << 24);
	return (SUCCESS);
}

static int8_t	draw_floor_ceiling(t_data *data)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		if (i < HEIGHT / 2)
			color = data->floor_color;
		else
			color = data->ceiling_color;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->background, j, i, color);
			j++;		
		}
		i++;
	}
	return (SUCCESS);
}

int8_t	image_handling(t_data *data)
{
	if (load_pngs(data) == FAILURE)
		return (err_msg(NULL, MLX2, FAILURE));
	if (load_rgb(data) == FAILURE)
		return (err_msg(NULL, MLX3, FAILURE));
	if (draw_floor_ceiling(data) == FAILURE)
		return (err_msg(NULL, MLX4, FAILURE));
	return (SUCCESS);
}