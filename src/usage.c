/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:08:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/08 22:50:01 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	delete_bonuses(t_data *data)
{
	if (data->tx_mini_wall)
		mlx_delete_texture(data->tx_mini_wall);
	if (data->tx_mini_floor)
		mlx_delete_texture(data->tx_mini_floor);
	if (data->tx_player1)
		mlx_delete_texture(data->tx_player1);
	if (data->tx_player2)
		mlx_delete_texture(data->tx_player2);
	if (data->tx_player3)
		mlx_delete_texture(data->tx_player3);
	if (data->im_mini_ray)
		mlx_delete_image(data->mlx, data->im_mini_ray);
	if (data->im_player1)
		mlx_delete_image(data->mlx, data->im_player1);
	if (data->im_player2)
		mlx_delete_image(data->mlx, data->im_player2);
	if (data->im_player3)
		mlx_delete_image(data->mlx, data->im_player3);
}

void	usage(void)
{
	ft_putstr_fd(USAGE1, 2);
	ft_putstr_fd(USAGE2, 2);
	ft_putstr_fd(USAGE3, 2);
	ft_putstr_fd(USAGE4, 2);
	ft_putstr_fd(USAGE5, 2);
	ft_putstr_fd(USAGE6, 2);
	ft_putstr_fd(USAGE7, 2);
	ft_putstr_fd(USAGE8, 2);
	ft_putstr_fd(USAGE9, 2);
	ft_putstr_fd(USAGE10, 2);
	ft_putstr_fd(USAGE11, 2);
	ft_putstr_fd(USAGE12, 2);
	ft_putstr_fd(USAGE13, 2);
}

void	wrap_up(t_data *data, int option)
{
	mlx_loop(data->mlx);
	if (option == 1)
		delete_bonuses(data);
	delete_images(data);
	mlx_terminate(data->mlx);
	free_data(data);
}
