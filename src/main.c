/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 main.c												:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: araveala <araveala@student.hive.fi>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/01 14:36:13 by fdessoy-		   #+#	  #+#			  */
/*   Updated: 2024/10/11 18:04:08 by araveala         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "../inc/cubd.h"

/*~~ main
1. make_array should be obsolete once data->map is filled, its for testing now 
2. initilize minimap is for the bonuse but utalized right now for visualizing 
map creation, player movement and ray casting for now , it allso collects p_x and p_y
untill parsing has handled that also
3. mlx_key_hook() is for player movement and esc key function 
4. mlx_loop(data->mlx) needs to be located where it is 
5. mlx_terminate seg faults at the moment , could be an issue of needing a flag
~~*/
int	main(int argc, char **argv)
{
	static t_data	*data; //~~ should it be static?

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
		// printf("bug hunting 1\n");
		printer(data);
		if (open_window(data) == 1)
		{
			printf("error requires freeing in main \n");
			return (-1);
		}
		//collect_ray(data); in minimap init for now
		// initilize_other?
		if (initlize_minimap(data) == 1)
		{
			printf("error requires freeing in main\n");
			return (-1);
		}
		mlx_key_hook(data->mlx, &keyhookfunc, data);
		//~~ bonus animation if wanted needs to start here
		// mlx_loop_hook(data->mlx, &animation_fucn, &data);
		mlx_loop(data->mlx);
		printer(data);
		free_array(data->file);
		//mlx_terminate(data->mlx);
	}
	else
		usage();
	printf("executed to the end\n");
	return (SUCCESS);
}
