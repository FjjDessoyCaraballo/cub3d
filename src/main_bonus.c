/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/08 16:48:23 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/** 
 * main
 * 
	1. initilize minimap is for the bonuse but utalized right now for visualizing 
	map creation, player movement and ray casting for now
	2. mlx_key_hook() is for player movement and esc key function 
	3. mlx_loop(data->mlx) needs to be located where it is 
	4. mlx_terminate seg faults at the moment , could be an issue of needing a flag
*/
int	main(int argc, char **argv)
{
	static t_data	*data;

	if (argc == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (err_msg(NULL, MALLOC, -1));
		if (map_handling(data, argv[1]) == FAILURE
			|| open_window(data) == FAILURE
			|| image_handling(data) == FAILURE
			|| initialize_minimap(data) == FAILURE
			|| init_player_texture(data) == FAILURE)
		{
			usage();
			free_data(data);
			return (FAILURE);
		}		
		mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
		mlx_set_instance_depth(data->im_ray->instances, 1);
		data->time = mlx_get_time();
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		mlx_loop_hook(data->mlx, &animation, data);
		mlx_loop_hook(data->mlx, &update, data);
		wrap_up(data, 1);
	}
	else
		usage();
	return (SUCCESS);
}
