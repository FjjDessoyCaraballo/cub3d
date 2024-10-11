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

/*~~ will be removed, only temporary ~~*/
static char **make_array(t_data *data)
{
	char **new_array = NULL;
	int i = 0;
	int x = 0;

	while (data->file[i])
		i++;
	new_array = ft_calloc(i + 1, sizeof(char *));
	if (new_array == NULL)
	{
		printf("malloc fail in make array\n");
		return (NULL);
	}
	while (x < i)
	{
		new_array[x] = ft_strdup(data->file[x]);
		if (new_array[x] == NULL)
		{
			x--;
			while (x >= 0)
			{
				free(new_array[x]);
				x--;
			}
			free(new_array);
			return (NULL);
		}
		x++;
	}
	new_array[x] = NULL;
	data->map_y = i;
	// assuming for now the map is a rectangle 
	data->map_x = ft_strlen(new_array[0]) - 1;
	return (new_array);
}

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
		if (map_handling(data, argv[1]) == 1)
			return (1);
		data->map = make_array(data); //remove
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
		printer(data->map);
		free_array(data->file);
		//free(data); // was casuing a double free
		//mlx_terminate(data->mlx);
	}
	else
		usage();
	printf("executed to the end\n");
	return (0);
}
