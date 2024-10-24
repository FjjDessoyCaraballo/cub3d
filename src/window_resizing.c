/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resizing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:33 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/24 09:52:53 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	resize_func(int32_t width, int32_t height, void *param)
{
	t_data *data;

	data = (t_data *)param;
	data->w_width = width;
	data->w_height = height;
	if (data->im_ray)
		mlx_delete_image(data->mlx, data->im_ray);
	data->im_ray = mlx_new_image(data->mlx, width, height);
	if (data->background)
		mlx_delete_image(data->mlx, data->background);
	data->background = mlx_new_image(data->mlx, width, height);
	draw_floor_ceiling(data);
}