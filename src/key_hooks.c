/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:03 by araveala          #+#    #+#             */
/*   Updated: 2024/10/17 12:52:13 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"


/*
~~cheat sheet~~
    1. key_pressed 0 = Set the key state to released
    2. key_pressed 1 = Set the key state to released
    3. end of game flag could be required should we allow player to loose
    4. step size could go in struct 
*/
void	keyhookfunc(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		if (data->mlx)
			mlx_close_window(data->mlx);
		else
			printf("mlx is null for some reason\n");
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->key_pressed[keydata.key] = 1;
	if (keydata.action == MLX_RELEASE)
		data->key_pressed[keydata.key] = 0;
	update_player(data);
}

/**
 * left and right arrows should spin you in either direction
 * wasd keys should move you around, drawing images here are 
 * bonus material used now for visualisation
 * of proggress 
 **/

void	update_player(t_data *data)
{
	if (data->key_pressed[MLX_KEY_RIGHT])
		rotate_player(data, ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_LEFT])
		rotate_player(data, -ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_W])
		move_player(data, STEP);
	if (data->key_pressed[MLX_KEY_S])
		move_player(data, -STEP);
	if (data->key_pressed[MLX_KEY_A])
		strafe_player(data, -STEP);
	if (data->key_pressed[MLX_KEY_D])
		strafe_player(data, STEP);
	
		//bonuses for minimap
	mlx_delete_image(data->mlx, data->im_ray);
	mlx_delete_image(data->mlx, data->im_mini_player);
	mlx_delete_image(data->mlx, data->im_map_player);

	draw_mini_map(data, 0, 0, 0); // bonus
	draw_mini_player(data);	
	
	draw_player(data);
	stack_ray_data(data, 0);
	mlx_image_to_window(data->mlx, data->im_mini_player, 0, 0);
	//mlx_image_to_window(data->mlx, data->im_map_player, 0, 0);
}
