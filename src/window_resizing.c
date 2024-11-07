/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resizing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:33 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/07 15:19:12 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	resize_func(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->im_ray)
		mlx_delete_image(data->mlx, data->im_ray);
	data->im_ray = mlx_new_image(data->mlx, width, height);
	if (data->background)
		mlx_delete_image(data->mlx, data->background);
	data->background = mlx_new_image(data->mlx, width, height);
	draw_floor_ceiling(data);
}
