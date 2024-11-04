/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/11/04 12:15:33 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Collects ray information based on when a wall is hit using a size of pixels
 */
double	calculate_initial_position(double position) 
{
	return (position * T_SIZE);
}

void	calculate_side_distances(t_data *data, double delta_dist_x, double delta_dist_y)
{
	if (data->ray_dir_x < 0) 
	{
        data->step_x = -1;
        data->side_dist_x = (data->ppos_pix_x - data->map_x * T_SIZE) * delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = ((data->map_x + 1) * T_SIZE - data->ppos_pix_x) \
			* delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
	data->step_y = -1;
	data->side_dist_y = (data->ppos_pix_y - data->map_y * T_SIZE) * delta_dist_y;
    }
	else
	{
		data->step_y = 1;
		data->side_dist_y = ((data->map_y + 1) * T_SIZE - data->ppos_pix_y) \
			* delta_dist_y;
	}
}

void	perform_dda(t_data *data, double delta_dist_x, double delta_dist_y) 
{
	data->side = 0;
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += delta_dist_x * T_SIZE;
			data->map_x += data->step_x;
			data->side = 0;
        }
		else
		{
			data->side_dist_y += delta_dist_y * T_SIZE;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (outof_bounds_check(data, data->map_y, data->map_x) == FAILURE
			|| data->map[data->map_y][data->map_x] == '1')
			data->hit = 1;
	}
}


double	calculate_perpendicular_distance(t_data *data)
{
	if (data->side == 0)
		return ((data->map_x * T_SIZE - data->ppos_pix_x) + (1 - data->step_x) \
			* T_SIZE / 2) / data->ray_dir_x;
	else
		return ((data->map_y * T_SIZE - data->ppos_pix_y) + (1 - data->step_y) \
			* T_SIZE / 2) / data->ray_dir_y;
}
/** Collect and draw a ray based on math~~angles, pie and radians
 * to calculate and draw each ray , collecting usable data for each ray, 
 * we increment per ray and rays angle. Collect_rays last argumentg is 0.0 
 * to reset every call:
 * 1. calculating angles and transalting degrees to radians for ray segments
 * that will be used to calculate distance;
 * 2. FOV field of view is degrees of view;
 * 3. DEG2RAD calculating degrees to radian from pi;
 * 4. RAY_MAX maximum number of rays we want (120) for now;
*/
void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
	double	delta_dist_x;
	double	delta_dist_y;
	
	delta_dist_x = fabs(1 / data->ray_dir_x);
	delta_dist_y = fabs(1 / data->ray_dir_y);
	data->ppos_pix_x = calculate_initial_position(data->x_ppos);
	data->ppos_pix_y = calculate_initial_position(data->y_ppos);
	data->map_x = (int)data->x_ppos;
	data->map_y = (int)data->y_ppos;
    calculate_side_distances(data, delta_dist_x, delta_dist_y);
    perform_dda(data, delta_dist_x, delta_dist_y);
    data->perp_wall_dist = calculate_perpendicular_distance(data);
    data->ray_len[i] = data->perp_wall_dist * cos(ray_angle - ray_distance);
    data->ray_hit[i] = find_direction(data->side, data->ray_dir_x, data->ray_dir_y);
}

