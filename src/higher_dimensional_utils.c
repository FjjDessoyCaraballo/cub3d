/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   higher_dimensional_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:08 by araveala          #+#    #+#             */
/*   Updated: 2024/11/06 17:29:15 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

 // Euclidean distance formula
double calculate_depth(t_data *data)
{
	double dx = data->map_x - data->x_ppos;
	double dy = data->map_y - data->y_ppos;
	return sqrt(dx * dx + dy * dy);
}

// Convert FOV from degrees to radians
double calculate_wall_width(double depth, double fov)
{ 
	double fov_radians = fov * (PI / 180.0); // Calculate the width of the wall based on the depth and FOV 
	return (2 * depth * tan(fov_radians / 2));
}

double diff(double wall_h)
{
	return (wall_h - HEIGHT);
}

double	get_inc(t_data *data, double w_h)
{
	
	double depth;
	double scale;
	
	depth = calculate_depth(data);
	scale = 1.0 / depth;
	//img_y_inc = get_inc(data, wall_h); in stretched wall and normal wall
	return (data->im_current_wall->height / w_h * scale);
}
