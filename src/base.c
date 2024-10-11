/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:41:48 by araveala          #+#    #+#             */
/*   Updated: 2024/10/09 16:31:28 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int open_window(t_data *data)
{
	//int window_width = data->map_x * 64;
    //int window_height = data->map_y * 64;
	//data->mlx = mlx_init(window_width, window_height, "cub3D", true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
	{
		printf("failed to initilize MLX \n");
		return (-1);
	}	
    return (0);
}
