/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:41:48 by araveala          #+#    #+#             */
/*   Updated: 2024/10/14 13:54:13 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int open_window(t_data *data)
{
	//int window_width = data->map_width * 64;
    //int window_height = data->map_length * 64;
	//data->mlx = mlx_init(window_width, window_height, "cub3D", true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
	{
		printf("failed to initilize MLX \n");
		return (-1);
	}	
    return (0);
}
