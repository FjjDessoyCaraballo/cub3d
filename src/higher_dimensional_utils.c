/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   higher_dimensional_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:08 by araveala          #+#    #+#             */
/*   Updated: 2024/11/07 11:25:26 by araveala         ###   ########.fr       */
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
void	calculate_hit_coords(t_data *data, int i)
{
	int	calc;

	if (data->side == 0)
	{
		if (data->step_x == -1)
			calc = 1;
		else
			calc = 0;
		data->ray_x = data->map_x + calc;
		data->ray_y = data->y_ppos + data->ray_len[i] * data->ray_dir_y;
	}
	else
	{
		if (data->step_y == -1)
			calc = 1;
		else
			calc = 0;
		data->ray_x = data->x_ppos + data->ray_len[i] * data->ray_dir_x;
		data->ray_y = data->map_y + calc;
	}
}
