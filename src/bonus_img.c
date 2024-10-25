/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:59:51 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/25 14:00:47 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	bonus_delete(t_data *data)
{
	mlx_delete_texture(data->tx_mini_floor);
	mlx_delete_texture(data->tx_mini_wall);
	mlx_delete_image(data->mlx, data->im_mini_floor);
	mlx_delete_image(data->mlx, data->im_mini_wall);
}

