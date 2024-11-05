/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:01:56 by araveala          #+#    #+#             */
/*   Updated: 2024/11/05 16:26:54 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/****this is the bonus version */
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

static void	player_pos(t_data *data, double new_x, double new_y)
{
	data->x_ppos = new_x;
	data->y_ppos = new_y;
	data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_map_player->instances[0].y = (data->y_ppos - 0.5) * MINI_T;
	data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * MINI_T;

}
void	strafe_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	char	map_char;

	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (-data->p_dir_y) * step;
	new_y = (data->y_ppos) + (data->p_dir_x) * step;
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
		if (map_char == '0' || map_char == '1')
			player_pos(data, new_x, new_y);
	}
}

// void	strafe_player(t_data *data, double step)
// {
// 	double	new_x;
// 	double	new_y;
// 	char	map_char;

// 	normalize_vector(&data->p_dir_x, &data->p_dir_y);
// 	new_x = (data->x_ppos) + (-data->p_dir_y) * step;
// 	new_y = (data->y_ppos) + (data->p_dir_x) * step;
// 	if ((new_x + data->radius) < 0
// 		|| (new_x - data->radius) > (data->map_width)
// 		|| (new_y + data->radius) < 0
// 		|| (new_y - data->radius) > (data->map_length))
// 		return ;
// 	if (new_x > data->map_width || new_y > data->map_length
// 		|| new_x < 0 || new_y < 0)
// 		return ;
// 	map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
// 	if (new_x < data->map_width && new_y < data->map_length)
// 	{	
// 		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
// 			return ;	
// 		if (map_char == '0')// || map_char == '1') //bonus ====== != '1')		
// 		{
// 			data->x_ppos = new_x;
// 			data->y_ppos = new_y;
// 			data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
// 			data->im_map_player->instances[0].y = (data->y_ppos - 0.5) * MINI_T;
// 			data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
// 			data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * MINI_T;
// 		}
// 	}
// }

/**
 * moving player so that they dont go out of bounds, challenge is
 * preventing entry to existing tiles that are marked space, ive 
 * left some solutions in theory but i will move on for now, 
 * as im not sure this will have much value to our project, 
 * especially since this problem should go away in the bonus
 * 1. floor and ceil are math.h functions, floor rounds 
 * down from decimal
*/
void	move_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	char	map_char;

	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (data->p_dir_x) * step;
	new_y = (data->y_ppos) + (data->p_dir_y) * step;
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
		if (map_char == '0' || map_char == '1')
			player_pos(data, new_x, new_y);
	}
}
// void	move_player(t_data *data, double step)
// {
// 	double	new_x;
// 	double	new_y;
// 	char	map_char;

// 	normalize_vector(&data->p_dir_x, &data->p_dir_y);
// 	new_x = (data->x_ppos) + (data->p_dir_x) * step;
// 	new_y = (data->y_ppos) + (data->p_dir_y) * step;
// 	if ((new_x + data->radius) < 0
// 		|| (new_x + data->radius) > (data->map_width)
// 		|| (new_y + data->radius) < 0
// 		|| (new_y + data->radius) > (data->map_length))
// 		return ;
// 	if (new_x < data->map_width && new_y < data->map_length)
// 	{
// 		if ((int)floor(new_y) < 0 || (int)floor(new_x) < 0)
// 			return ;
// 		map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
// 		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
// 			return ;
// 		}
// 		if (map_char == '0')
// 		{
// 			data->x_ppos = new_x;
// 			data->y_ppos = new_y;
// 			data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
// 			data->im_map_player->instances[0].y = (data->y_ppos -  0.5) * MINI_T;
// 			data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
// 			data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * MINI_T;
// 		}
// 	}
// }

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
