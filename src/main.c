/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/31 15:07:01 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	initializer(t_data *data)
{
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (err_msg(NULL, MALLOC, -1));
	data->img = ft_calloc(1, sizeof(t_img));
	if (!data->img)
		return (err_msg(NULL, MALLOC, -1));
	data->texture = ft_calloc(1, sizeof(t_texture));
	if (!data->texture)
		return (err_msg(NULL, MALLOC, -1));
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
	static t_data	data;

	if (argc == 2)
	{
		if (initializer(&data)
			|| map_handling(&data, argv[1]) == FAILURE
			|| open_window(&data) == FAILURE
			|| image_handling(&data) == FAILURE
			|| initlize_minimap(&data) == FAILURE)
		{
			usage();
			free_data(&data);
			return (FAILURE);
		}
		data->exact_x = data->x_ppos * T_SIZE / 2;
		data->exact_y = data->y_ppos * T_SIZE / 2;
		stack_ray_data(data, 0);
		//mlx_image_to_window(data->mlx, data->im_ray, 0, 0); //WIDTH, HEIGHT);
		// collect_ray(data); in minimap init for now
		// **init_3d(data);
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		//~~ bonus animation if wanted needs to start here
		// mlx_loop_hook(data->mlx, &animation_fucn, &data);
		mlx_loop(data->mlx);
		free_data(data);
		mlx_terminate();
	}
	else
		usage();
	printf("executed to the end\n");
	return (SUCCESS);
}
