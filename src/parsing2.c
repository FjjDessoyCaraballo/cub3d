/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:05 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 10:13:46 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	floor_information(t_data *data)
{
	int	index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "F", 1))
		{
			data->floor_info = ft_strdup(data->file[index]);
			if (!data->floor_info)
				return (FAILURE);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	ceiling_information(t_data *data)
{
	int	index;

	index = 0;
	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "C", 1))
		{
			data->ceiling_info = ft_strdup(data->file[index]);
			if (!data->ceiling_info)
				return (FAILURE);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	sprites_information(t_data *data)
{
	if (search_sprites(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	map_information(t_data *data)
{
	int	index;

	index = 0;
	while(data->file[index])
	{
		index++;
	}
	return (SUCCESS);
}

int8_t	extract(t_data *data)
{
	if (floor_information(data) == FAILURE)
		return (FAILURE);
	if (ceiling_information(data) == FAILURE)
	{
		free(data->floor_info);
		return (FAILURE);
	}
	if (sprites_information(data) == FAILURE)
	{
		free(data->floor_info);
		free(data->ceiling_info);
		return (FAILURE);
	}
	if (map_information(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


