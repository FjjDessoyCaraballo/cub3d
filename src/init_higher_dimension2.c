/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:37:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/04 14:16:55 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Find which wall texture to draw based on direction
 * 
 * @param data data structure to be passed down
 * @param i index given previously
 */
int	find_wall(t_data *data, int i)
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
	return (SUCCESS);
}

/** 
 * Finds the wall and checks for failure
 * 
 * @param data data structure to be passed down
 * @param i index given previously
*/
int	check_for_wall_failure(t_data *data, int i)
{
	if (find_wall(data, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
