/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension2_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:37:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/14 16:58:54 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int	find_door(t_data *data)
{	
	if (data->map_x == data->dpos_x && data->map_y == data->dpos_y)
	{
		if (data->side == 1 && data->map_y == data->dpos_y)
		{
			if (data->door_flag == 0)
				data->im_current_wall = data->im_door1;
			else if (data->door_flag == 1)
				data->im_current_wall = data->im_door2;
			else if (data->door_flag == 2)
				data->im_current_wall = data->im_door3;
			return (SUCCESS);
		}
		else if (data->side == 0 && data->map_x == data->dpos_x)
		{
			if (data->door_flag == 0)
				data->im_current_wall = data->im_door1;
			else if (data->door_flag == 1)
				data->im_current_wall = data->im_door2;
			else if (data->door_flag == 2)
				data->im_current_wall = data->im_door3;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

/**
 * Find which wall texture to draw based on direction
 * 
 * @param data data structure to be passed down
 * @param i index given previously
 */
int	find_wall(t_data *data, int i)
{
	if (find_door(data) == FAILURE)
	{
		if (data->ray_hit[i] == NORTH)
			data->im_current_wall = data->im_n_wall;
		else if (data->ray_hit[i] == SOUTH)
			data->im_current_wall = data->im_s_wall;
		else if (data->ray_hit[i] == EAST)
			data->im_current_wall = data->im_e_wall;
		else if (data->ray_hit[i] == WEST)
			data->im_current_wall = data->im_w_wall;
		if (data->im_current_wall == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

/** 
 * Finds the wall and checks for failure
 * 
 * @param data data structure to be passed down
 * 
 * @param i index given previously
 * 
*/
int	check_for_wall_failure(t_data *data, int i)
{
	if (find_wall(data, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	handle_door(t_data *data)
{
	double	diff_x;
	double	diff_y;

	diff_x = data->dpos_x - data->ppos_pix_x / T_SIZE;
	diff_y = data->dpos_y - data->ppos_pix_y / T_SIZE;
	if ((diff_x >= -1.5 && diff_x <= 1) && (diff_y >= -1.5 && diff_y <= 0.9))
	{
		if (data->door_flag == 0)
			data->door_flag++;
		else if (data->door_flag == 1)
			data->door_flag++;
		else if (data->door_flag == 2)
			data->door_flag = 0;
	}
}
