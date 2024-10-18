/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/17 14:08:55 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

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
			// printer(data);
			usage();
			free_data(data);
			return (FAILURE);
		}
		printer(data);
		if (open_window(data) == FAILURE)
		{
			printf("error requires freeing in main \n");
			return (FAILURE);
		}
		// collect_ray(data); in minimap init for now
		// **init_3d(data);
		if (initlize_minimap(data) == FAILURE)
		{
			printf("error requires freeing in main\n");
			return (FAILURE);
		}
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		//~~ bonus animation if wanted needs to start here
		// mlx_loop_hook(data->mlx, &animation_fucn, &data);
		mlx_loop(data->mlx);
		printer(data);
		// if (flag == true)
		{
			// free_array(data->file);
			// mlx_terminate(data->mlx);
		}
	}
	else
		usage();
	printf("executed to the end\n");
	return (SUCCESS);
}
