/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:03 by araveala          #+#    #+#             */
/*   Updated: 2024/11/14 15:05:19 by fdessoy-         ###   ########.fr       */
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

void	animation(void *param)
{
	t_data		*data;
	double		time_in;

	data = (t_data *)param;
	time_in = mlx_get_time();
	if (time_in - data->time >= 0.2)
	{
		if (data->im_player1->instances[0].enabled == false)
		{
			data->im_player1->instances[0].enabled = true;
			data->im_player3->instances[0].enabled = false;
		}
		else if (data->im_player2->instances[0].enabled == false)
		{
			data->im_player2->instances[0].enabled = true;
			data->im_player3->instances[0].enabled = false;
		}
		else if (data->im_player3->instances[0].enabled == false)
		{
			data->im_player3->instances[0].enabled = true;
			data->im_player1->instances[0].enabled = false;
			data->im_player2->instances[0].enabled = false;
		}
		data->time = time_in;
	}
}

/**
 * 
 * Enables isntance on or off depending on if it was already
 * on or off
 * 
 * @param data , struct that carries most of our variables
 * 
 */
void	toggle_minimap(t_data *data)
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
}

/**
 *
 * Get the key press and assign if .key is on(1) or off(0)
 * Then move player by updating postion
 *  1. key_pressed 0 = Set the key state to release
 *	2. key_pressed 1 = Set the key state to released
 * 
 * Toggle minimap seperated as we do not want action on 
 * continuous key press
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
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_SPACE)
		handle_door(data);
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
