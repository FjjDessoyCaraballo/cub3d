/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonuses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:29:03 by araveala          #+#    #+#             */
/*   Updated: 2024/11/14 12:01:05 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int	find_door_location(t_data *data)
{
	data->door_y = 4;// * T_SIZE;//(int)data->x_ppos + 2;
	data->door_x = 23;// * T_SIZE;//(int)data->y_ppos + 1; 
	/*int x;
	int y;
	int count;
	int	max;
	
	x = (int)data->x_ppos + 0.5;
	y = (int)data->y_ppos + 0.5;
	count = 0;
	max = 10;

	while (y >= 0 && data->map[y - 1][x] != '1')
		y--;
	printf("start what is x = %d and y = %d\n", x, y);
	while (count <= max)
	{
		while (y - 1 >= 0 && data->map[y - 1][x] == '1')
		{
			if (x < data->map_width && data->map[y][x] != '1')
			{
				x++;
				count++;
			}
			if (count >= max)
			{
				printf("return x = %d and y = %d\n", x, y);
				data->door_y = y - 1;
				data->door_x = x;
				return (max);
			}
			if (data->map[y][x + 1] == '1' && data->map[y - 1][x] == '1')	
				y++;
		}
		printf("before 2what is x = %d and y = %d\n", x, y);
		while (x + 1 < data->map_width && data->map[y][x + 1] == '1')
		{
			if (y < data->map_length && data->map[y][x] != '1')
			{
				y++;
				count++;	
			}
			if (count >= max)
			{
				printf("return x = %d and y = %d\n", x, y);
				data->door_y = y;
				data->door_x = x + 1;
				return (max);
			}
			printf("2what is x = %d and y = %d\n", x, y);
			if (data->map[y + 1][x] == '1' && data->map[y][x + 1] == '1')	
				x--;
		}
		
		while (y + 1 < data->map_length && data->map[y + 1][x] == '1')
		{
			if (x -1 >= 0 && data->map[y][x - 1] != '1')
			{
				printf("minusing x\n");
				x--;
				count++;
			}
			if (count >= max)
			{
				printf("return x = %d and y = %d\n", x, y);
				data->door_y = y + 1;
				data->door_x = x;
				return (max);
			}
			printf("3what is x = %d and y = %d\n", x, y);
			if (data->map[y + 1][x] == '1' && data->map[y][x + 1] == '1')
				y++;
		}
		while (x - 1 >= 0 && data->map[y][x - 1] == '1')
		{
			if (y + 1 < data->map_length && data->map[y + 1][x] != '1')
			{
				y++;
				count++;	
			}
			if (count >= max)
			{
				printf("return x = %d and y = %d\n", x, y);
				data->door_y = y;
				data->door_x = x - 1;
				return (max);
			}
			printf("4what is x = %d and y = %d\n", x, y);	
			if (data->map[y + 1][x] == '1' && data->map[y][x - 1] == '1')	
				x++;
		}
	}*/
	return (SUCCESS);
}

int	load_player_imgs(t_data *data)
{	
	data->im_player1 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_player2 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_player3 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_player1 == NULL || data->im_player2 == NULL
		|| data->im_player3 == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	data->tx_player1 = mlx_load_png("./textures/rathand1.png");
	data->tx_player2 = mlx_load_png("./textures/rathand2.png");
	data->tx_player3 = mlx_load_png("./textures/rathand3.png");
	if (data->tx_player1 == NULL || data->tx_player2 == NULL
		|| data->tx_player3 == NULL)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_player1 = mlx_texture_to_image(data->mlx, data->tx_player1);
	data->im_player2 = mlx_texture_to_image(data->mlx, data->tx_player2);
	data->im_player3 = mlx_texture_to_image(data->mlx, data->tx_player3);
	if (data->im_player1 == NULL || data->im_player2 == NULL
		|| data->im_player3 == NULL)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	return (SUCCESS);
}

int	set_player(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->im_player1, WIDTH / 2, 659) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	if (mlx_image_to_window(data->mlx, data->im_player2, WIDTH / 2, 659) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	if (mlx_image_to_window(data->mlx, data->im_player3, WIDTH / 2, 659) == -1)
		return (err_msg(NULL, IMG_TO_WIN, FAILURE));
	mlx_resize_image(data->im_player1, 420, 420);
	mlx_resize_image(data->im_player2, 420, 420);
	mlx_resize_image(data->im_player3, 420, 420);
	mlx_set_instance_depth(data->im_player1->instances, 2);
	mlx_set_instance_depth(data->im_player2->instances, 2);
	mlx_set_instance_depth(data->im_player3->instances, 2);
	data->im_player1->instances[0].enabled = 0;
	data->im_player2->instances[0].enabled = 0;
	data->im_player3->instances[0].enabled = 1;
	return (SUCCESS);
}

int	init_player_texture(t_data *data)
{
//	find_door_location(data);
//	printf("check door x = %f door y = %f\n", data->door_x, data->door_y);

	if (load_player_imgs(data) == FAILURE)
		return (FAILURE);
	if (set_player(data) == FAILURE)
		return (FAILURE);
	data->im_door1 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_door2 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_door3 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	
	data->tx_door1 = mlx_load_png("./textures/round_door.png");
	data->tx_door2 = mlx_load_png("./textures/round_door2.png");
	data->tx_door3 = mlx_load_png("./textures/round_door3.png");
	
	data->im_door1 = mlx_texture_to_image(data->mlx, data->tx_door1);
	data->im_door2 = mlx_texture_to_image(data->mlx, data->tx_door2);
	data->im_door3 = mlx_texture_to_image(data->mlx, data->tx_door3);
	data->door_flag = 0;
	//testing only so far
	//find location for door 
	return (SUCCESS);
}
