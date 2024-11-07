/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:08:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/07 16:10:30 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

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
}

void	wrap_up(t_data *data)
{
	mlx_loop(data->mlx);
	delete_images(data);
	mlx_terminate(data->mlx);
	free_data(data);
}
