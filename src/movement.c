/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:01:56 by araveala          #+#    #+#             */
/*   Updated: 2024/10/11 18:33:47 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/*void initialize_player_direction(t_data *data, char initial_facing) {
	if (initial_facing == 'N') {
		data->p_dir_x = 0;
		data->p_dir_y = -1;
	} else if (initial_facing == 'S') {
		data->p_dir_x = 0;
		data->p_dir_y = 1;
	} else if (initial_facing == 'E') {
		data->p_dir_x = 1;
		data->p_dir_y = 0;
	} else if (initial_facing == 'W') {
		data->p_dir_x = -1;
		data->p_dir_y = 0;
	}
}*/
/*~~ bonus stuff but easier for visualisation~~*/
/*static void	update_array(t_data *data, int flag)
{
	data->map[data->p_y][data->p_x] = '0';
	if (flag == 1)
		data->p_x = data->p_x + 1;
	if (flag == 2)
		data->p_x = data->p_x - 1;
	if (flag == 3)
		data->p_y = data->p_y + 1;
	if (flag == 4)
		data->p_y = data->p_y - 1;
	data->map[data->p_y][data->p_x] = 'N'; // this should adjust to which way we are facing
	//d->steps += 1;
}*/

/*~~ the offsets are due to out of bounds calculation comparing to the middle of p_x and p_y ~~*/
void	strafe_player(t_data *data, double step_x, double step_y)
{
	double	sq;
	double	new_x;
	double	new_y;
	double	radius;

	radius = 10.0 / 64.0 + STEP;
	sq = sqrt(data->p_dir_x * data->p_dir_x + data->p_dir_y * data->p_dir_y);
	new_x = data->p_x + (-data->p_dir_y / sq) * step_x;
	new_y = data->p_y + (data->p_dir_x / sq) * step_y;
	if ((new_x + radius) < -0.25 || (new_x - radius) >= (data->map_x - 0.75) || (new_y + radius) < -0.25 || (new_y - radius) >= (data->map_y - 0.75))
	{
		printf("Out of bounds\n");
		return ;
	}
	if (data->map[(int)new_y][(int)new_x] == '0' || data->map[(int)new_y][(int)new_x] == '1') //bonus ====== != '1')
	{
		data->p_x = new_x;
		data->p_y = new_y;
	}
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	*x /= length;
	*y /= length;
}

void	move_player(t_data *data, double step_x, double step_y)
{
	double	sq;
	double	new_x;
	double	new_y;
	double	radius;

	radius = 10.0 / 64.0 + STEP;
	sq = sqrt(data->p_dir_x * data->p_dir_x + data->p_dir_y * data->p_dir_y);
	new_x = data->p_x + (data->p_dir_x / sq) * step_x;
	new_y = data->p_y + (data->p_dir_y / sq) * step_y;
	if ((new_x + radius) < -0.25 || (new_x - radius) >= (data->map_x - 0.75) || (new_y + radius) < -0.25 || (new_y - radius) >= (data->map_y - 0.75))
	{
		printf("Out of bounds\n");
		return ;
	}
	if (data->map[(int)new_y][(int)new_x] == '0' || data->map[(int)new_y][(int)new_x] == '1') //bonus ====== != '1')
	{
		data->p_x = new_x;
		data->p_y = new_y;
	}
}

void	rotate_player(t_data *data, double angle)
{
	double	prev_dir_x;

	prev_dir_x = data->p_dir_x;
	data->p_dir_x = data->p_dir_x * cos(angle) - data->p_dir_y * sin(angle);
	data->p_dir_y = prev_dir_x * sin(angle) + data->p_dir_y * cos(angle);
	normalize_vector(&data->p_dir_x, &data->p_dir_y);
}

/* stick this in keyhooks .c */
/*~~ left and right arrows should spin you in either direction
wasd keys should move you around, this means that */
void	update_player(t_data *data)
{
	if (data->key_pressed[MLX_KEY_RIGHT])
		rotate_player(data, ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_LEFT])
		rotate_player(data, -ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_W])
		move_player(data, STEP, STEP);
	if (data->key_pressed[MLX_KEY_S])
		move_player(data, -STEP, -STEP);
	if (data->key_pressed[MLX_KEY_A])
		strafe_player(data, -STEP, -STEP);
	if (data->key_pressed[MLX_KEY_D])
		strafe_player(data, STEP, STEP);
		//bonuses for minimap
	mlx_delete_image(data->mlx, data->im_ray);
	mlx_delete_image(data->mlx, data->im_mini_player);
	draw_player(data);
	stack_ray_data(data, 0);
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->im_mini_player, 0, 0);
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
