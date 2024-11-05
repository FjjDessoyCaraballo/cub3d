/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/05 15:13:35 by fdessoy-         ###   ########.fr       */
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
			|| initlize_minimap(data) == FAILURE)
		{
			usage();
			free_data(data);
			return (FAILURE);
		}
		data->x_ppos += 0.5;
		data->y_ppos += 0.5;
		stack_ray_data(data, 0);
		mlx_image_to_window(data->mlx, data->im_map, 0, 0);
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		draw_mini_map(data, 0, 0, 0);
		wrap_up(data);
	}
	else
		usage();
	return (SUCCESS);
}
