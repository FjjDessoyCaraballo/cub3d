/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:30:57 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 10:55:39 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	free_data(t_data *data)
{
	if (data->e_sprite)
		free(data->e_sprite);
	if (data->n_sprite)
		free(data->n_sprite);
	if (data->s_sprite)
		free(data->s_sprite);
	if (data->w_sprite)
		free(data->w_sprite);
	if (data->ceiling_info)
		free(data->ceiling_info);
	if (data->floor_info)
		free(data->floor_info);
	if (data->map)
		free_array(data->map);
	if (data->file)
		free_array(data->file);
	free(data);
}