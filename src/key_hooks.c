/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:03 by araveala          #+#    #+#             */
/*   Updated: 2024/11/08 15:39:12 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	update(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	update_player(data);
	stack_ray_data(data, 0);
}

/**
 *
 * Get the key press and assign if .key is on(1) or off(0)
 * Then move player by updating postion
 *  1. key_pressed 0 = Set the key state to release
 *	2. key_pressed 1 = Set the key state to released
 * 
 * 	@param keydata MLX key call back data
 *	@param param data , struct that carries most of our variables
 *  
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
}

/**
 * Moves player based on key press
 * left and right arrows should spin you in either direction
 * wasd keys should move you around
 * 
 * Then starts a new ray iteration
 * 
 * @param data struct that carries most of our variables
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
}
