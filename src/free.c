/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:30:57 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 12:34:53 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	free_data(t_data *data)
{
	free(data->e_sprite);
	free(data->n_sprite);
	free(data->s_sprite);
	free(data->w_sprite);
	free(data->ceiling_info);
	free(data->floor_info);
	free_array(data->file);
	free(data);
}