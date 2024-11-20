/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:01:56 by araveala          #+#    #+#             */
/*   Updated: 2024/11/20 12:34:53 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * This computes the magnitude of the vector using the 
 * Pythagorean theorem, to simplyfy our directin numbers in an attempt to 
 * make math on these numbers easier.
*/
void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	*x /= length;
	*y /= length;
}

/**
 * Updates player position aswell us updating the image instances positions
 * on the minimpa
 * @param data struct that carries most of our variables
 * @param new_x the new calculated position x
 * @param new_y the new calculated position y
 * 
 */
static void	player_pos(t_data *data, double new_x, double new_y)
{
	data->x_ppos = new_x;
	data->y_ppos = new_y;
	data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * data->mini_t;
	data->im_map_player->instances[0].y = (data->y_ppos - 0.5) * data->mini_t;
	data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * data->mini_t;
	data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * data->mini_t;
}

/**
 * 
 * Moves the player left or right
 * and updating player position based on valid movements only
 * 
 * @param data struct that carries most of our variables
 * @param step the size of step given as either + or - depending on direction
 * 
 */
void	strafe_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	char	map_char;

	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (-data->p_dir_y) * step / 20;
	new_y = (data->y_ppos) + (data->p_dir_x) * step / 20;
	if ((new_x + data->radius) < 0
		|| (new_x - data->radius) > (data->map_width)
		|| (new_y + data->radius) < 0
		|| (new_y - data->radius) > (data->map_length))
		return ;
	if (new_x > data->map_width || new_y > data->map_length
		|| new_x < 0 || new_y < 0)
		return ;
	map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
	if (new_x < data->map_width && new_y < data->map_length)
	{	
		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
			return ;
		if (map_char == '0' || check_player_strafe(data, new_x, new_y) == 0)
			player_pos(data, new_x, new_y);
	}
}

/**
 * Move the player up or down and
 * updates player position based on valid movements only
 * 
 * @param data struct that carries most of our variables
 * @param step size of step given as + or - depending on direction
 * 
*/
void	move_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	char	map_char;

	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (data->p_dir_x) * step / 15;
	new_y = (data->y_ppos) + (data->p_dir_y) * step / 15;
	if ((new_x + data->radius) < 0
		|| (new_x + data->radius) > (data->map_width)
		|| (new_y + data->radius) < 0
		|| (new_y + data->radius) > (data->map_length))
		return ;
	if (new_x < data->map_width && new_y < data->map_length)
	{
		if ((int)floor(new_y) < 0 || (int)floor(new_x) < 0)
			return ;
		map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
			return ;
		if (map_char == '0' || check_player(data, new_x, new_y) == 0)
			player_pos(data, new_x, new_y);
	}
}

/**
 * Rotates the player on center axis,
 * and updates the direction marker(mini_line)
 * 
 * @param data struct that carries most of our variables
 * @param angle calculated angle based on our iterator =
 * (which ray we are woking with)
 * 
 */
void	rotate_player(t_data *data, double angle)
{
	double	prev_dir_x;

	wipe_line(data, 0, 0);
	prev_dir_x = data->p_dir_x;
	data->p_dir_x = data->p_dir_x * cos(angle) - data->p_dir_y * sin(angle);
	data->p_dir_y = prev_dir_x * sin(angle) + data->p_dir_y * cos(angle);
	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	draw_mini_line(data, 0, 0);
}
