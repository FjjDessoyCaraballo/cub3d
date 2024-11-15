/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   higher_dimensional_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:08 by araveala          #+#    #+#             */
/*   Updated: 2024/11/15 14:11:01 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Takes the difference between our wall hit from the dda and the payer position
 * 
 * @param data struct that carries most of our variables
 * 
 * @return Euclidean distance (depth)
 */
double	calculate_depth(t_data *data)
{
	double	dx;
	double	dy;

	dx = data->map_x - data->x_ppos;
	dy = data->map_y - data->y_ppos;
	return (sqrt(dx * dx + dy * dy));
}

/**
 * @param wall_h pre calculated height of wall to be drawn
 */
double	diff(double wall_h)
{
	return (wall_h - HEIGHT);
}

/**
 * 
 * We calculate and store the exact location of the wall hit in pixels
 * and if we hit a vertical(0) or horizontal(1) wall
 * 
 * @param data struct that carries most of our variables
 * @param i iterator that signals which ray we are collecting
 * 
 */
void	calculate_hit_coords(t_data *data)
{
	int	calc;

	if (data->side == 0)
	{
		if (data->step_x == -1)
			calc = 1;
		else
			calc = 0;
		data->ray_x = data->map_x + calc;
		data->ray_y = data->ppos_pix_y + data->perp_wall_dist * data->ray_dir_y;
	}
	else
	{
		if (data->step_y == -1)
			calc = 1;
		else
			calc = 0;
		data->ray_x = data->ppos_pix_x + data->perp_wall_dist * data->ray_dir_x;
		data->ray_y = data->map_y + calc;
	}
}

int	check_player_strafe(t_data *data, double diff_x, double diff_y)
{
	double	check_x;
	double	check_y;

	check_x = -data->p_dir_y;
	check_y = data->p_dir_x;
	diff_x = data->dpos_x - data->ppos_pix_x / T_SIZE;
	diff_y = data->dpos_y - data->ppos_pix_y / T_SIZE;
	if ((diff_x >= -2.0 && diff_x <= 0.9) && (diff_y >= -2.0
			&& diff_y <= 0.9) && data->door_flag > 0)
		return (0);
	if (fabs(data->x_ppos - check_x) > fabs(data->y_ppos - check_y))
	{
		if (data->map[(int)data->y_ppos][(int)ceil(data->x_ppos + 1)] == '1')
			return (1);
	}
	if (fabs(data->y_ppos - check_y) > fabs(data->x_ppos - check_x))
	{
		if (data->map[(int)data->y_ppos][(int)ceil(data->x_ppos + 1)] == '1')
			return (1);
	}
	return (1);
}

int	check_player(t_data *data, double diff_x, double diff_y)
{
	double	check_x;
	double	check_y;

	check_x = fabs(data->p_dir_x);
	check_y = fabs(data->p_dir_y);
	diff_x = data->dpos_x - data->ppos_pix_x / T_SIZE;
	diff_y = data->dpos_y - data->ppos_pix_y / T_SIZE;
	if ((diff_x >= -2.0 && diff_x <= 0.9) && (diff_y >= -2.0
			&& diff_y <= 0.9) && data->door_flag > 0)
		return (0);
	if (fabs(check_x) > fabs(check_y))
	{
		if (data->map[(int)data->y_ppos][(int)ceil(data->x_ppos + 1)] == '1')
			return (1);
	}	
	else
	{
		if (data->map[(int)ceil(data->y_ppos + 1)][(int)data->x_ppos] == '1')
			return (1);
	}
	return (1);
}
