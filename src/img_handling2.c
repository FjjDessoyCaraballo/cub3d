/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:28:46 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/04 14:08:33 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Find the colour from the textures specified pixel should be drawn next
 */
uint32_t	fetch_pixel_rgb(mlx_image_t *img, int x, int y, int pos)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (img != NULL)
	{
		pos = (y * img->width + x) * 4;
		r = img->pixels[pos];
		g = img->pixels[pos + 1];
		b = img->pixels[pos + 2];
		a = img->pixels[pos + 3];
		return (load_rgb(r, g, b, a));
	}
	return (0);
}

void	delete_pngs(t_data *data)
{
	mlx_delete_texture(data->tx_n_wall);
	mlx_delete_texture(data->tx_s_wall);
	mlx_delete_texture(data->tx_e_wall);
	mlx_delete_texture(data->tx_w_wall);
}

void	delete_images(t_data *data)
{
	mlx_delete_image(data->mlx, data->im_n_wall);
	mlx_delete_image(data->mlx, data->im_e_wall);
	mlx_delete_image(data->mlx, data->im_w_wall);
	mlx_delete_image(data->mlx, data->im_s_wall);
	mlx_delete_image(data->mlx, data->background);
	mlx_delete_image(data->mlx, data->im_ray);
	mlx_delete_image(data->mlx, data->im_map);
	mlx_delete_image(data->mlx, data->im_mini_floor);
	mlx_delete_image(data->mlx, data->im_mini_player);
	mlx_delete_image(data->mlx, data->im_map_player);
	mlx_delete_image(data->mlx, data->im_current_wall);
}
