/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:03 by araveala          #+#    #+#             */
/*   Updated: 2024/11/05 15:27:36 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"


int	toggle_minimap(t_data *data)
{
	if (data->im_map->instances[0].enabled == 0)
	{
		data->im_map->instances[0].enabled = 1;
		data->im_map_player->instances[0].enabled = 1;
		data->im_mini_ray->instances[0].enabled = 1;
	}
	else
	{
		data->im_map->instances[0].enabled = 0;
		data->im_map_player->instances[0].enabled = 0;
		data->im_mini_ray->instances[0].enabled = 0;	
	}
	return (0); // could be void
}
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

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			data->key_pressed[keydata.key] = 1;
		if (keydata.action == MLX_RELEASE)
			data->key_pressed[keydata.key] = 0;
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		toggle_minimap(data);
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
	stack_ray_data(data, 0);
}
