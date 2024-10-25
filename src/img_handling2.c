/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:51:03 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/25 14:03:09 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	delete_textures(t_data *data)
{
	mlx_delete_texture(data->tx_n_wall);
	mlx_delete_texture(data->tx_s_wall);
	mlx_delete_texture(data->tx_e_wall);
	mlx_delete_texture(data->tx_w_wall);
}

void	delete_images(t_data *data)
{
	mlx_delete_image(data->mlx, data->im_n_wall);
	mlx_delete_image(data->mlx, data->im_w_wall);
	mlx_delete_image(data->mlx, data->im_e_wall);
	mlx_delete_image(data->mlx, data->im_s_wall);
	mlx_delete_image(data->mlx, data->background);
}