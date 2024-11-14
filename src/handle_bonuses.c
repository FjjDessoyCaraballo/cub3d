/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonuses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:29:03 by araveala          #+#    #+#             */
/*   Updated: 2024/11/14 13:03:24 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int	find_door_location(t_data *data)
{
	data->door_y = 4;
	data->door_x = 23;
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

int	set_door(t_data *data)
{
	data->im_door1 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_door2 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->im_door3 = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->im_door1 == NULL || data->im_door2 == NULL || data->im_door3 == NULL)
		return (err_msg(NULL, NEW_IMG, FAILURE));
	data->tx_door1 = mlx_load_png("./textures/round_door.png");
	data->tx_door2 = mlx_load_png("./textures/round_door2.png");
	data->tx_door3 = mlx_load_png("./textures/round_door3.png");
	if (data->tx_door1 == NULL || data->tx_door2 == NULL || data->tx_door3 == NULL)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_door1 = mlx_texture_to_image(data->mlx, data->tx_door1);
	data->im_door2 = mlx_texture_to_image(data->mlx, data->tx_door2);
	data->im_door3 = mlx_texture_to_image(data->mlx, data->tx_door3);
	if (data->im_door1 == NULL || data->im_door2 == NULL || data->im_door3 == NULL)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	data->door_flag = 0;
	return (SUCCESS);
}

int	init_player_texture(t_data *data)
{
	if (load_player_imgs(data) == FAILURE)
		return (FAILURE);
	if (set_player(data) == FAILURE)
		return (FAILURE);
	if (set_door(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
