/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/01 16:38:23 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * We finalize the scenery by putting images to window , adjusting the mini player 
 * and setting the layering depths of the images so they all display correctly.
 */
int	set_view(t_data * data)
{
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->im_map, 0, 0);
	mlx_image_to_window(data->mlx, data->im_map_player, 0, 0);
	mlx_image_to_window(data->mlx, data->im_mini_ray,  0, 0);
	data->im_map_player->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_map_player->instances[0].y = (data->y_ppos - 0.5) * MINI_T;	
	mlx_set_instance_depth(data->im_ray->instances, 1);
	mlx_set_instance_depth(data->im_map->instances, 2);
	mlx_set_instance_depth(data->im_map_player->instances, 3);	
	mlx_set_instance_depth(data->im_mini_ray->instances, 4);
	//errr??
	data->im_mini_ray->instances[0].x = (data->x_ppos - 0.5) * MINI_T;
	data->im_mini_ray->instances[0].y = (data->y_ppos - 0.5) * MINI_T;	

	return(0); //success
}

/*~~ main
1. initilize minimap is for the bonuse but utalized right now for visualizing 
map creation, player movement and ray casting for now
2. mlx_key_hook() is for player movement and esc key function 
3. mlx_loop(data->mlx) needs to be located where it is 
4. mlx_terminate seg faults at the moment , could be an issue of needing a flag
~~*/
int	main(int argc, char **argv)
{
	static t_data	*data;

	if (argc == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (err_msg(NULL, MALLOC, -1));
		if (map_handling(data, argv[1]) == FAILURE)
		{
			usage();
			free_data(data);
			return (FAILURE);
		}
		if (open_window(data) == FAILURE)
			return (FAILURE);
		if (image_handling(data) == FAILURE)
			return (FAILURE);
		stack_ray_data(data, 0);
		if (initlize_minimap(data) == FAILURE)
			return (FAILURE);
		set_view(data);
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		//~~ bonus animation if wanted needs to start here
		// mlx_loop_hook(data->mlx, &animation_fucn, &data);
		mlx_loop(data->mlx);
	}
	else
		usage();
	printf("executed to the end\n");
	return (SUCCESS);
}
