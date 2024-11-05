/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:41:48 by araveala          #+#    #+#             */
/*   Updated: 2024/11/04 14:05:01 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * The idea is to create any base requirements for having a window open
 * and any quick data collection, this file itself may become obsolete
 * if there is n othing else to do here, MLX42 does make it simple.
 * 
 * @param data structt that carries the mlx instances we loop
 * 
 * @return FAILURE 1 or SUCCESS 0
 */
int	open_window(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
		return (err_msg(NULL, MLX1, FAILURE));
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	return (SUCCESS);
}
