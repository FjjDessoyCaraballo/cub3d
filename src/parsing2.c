/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:05 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 15:36:34 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	floor_information(t_data *data)
{
	int		index;
	char	*floor;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "F", 1))
		{
			floor = ft_strdup(data->file[index]);
			if (!floor)
				return (FAILURE);
			if (rgb_parse(data, floor, 1) == FAILURE)
			{
				free(floor);
				return (FAILURE);
			}
			free(floor);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	ceiling_information(t_data *data)
{
	int		index;
	char	*ceiling;

	index = 0;
	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "C", 1))
		{
			ceiling = ft_strdup(data->file[index]);
			if (!ceiling)
				return (FAILURE);
			if (rgb_parse(data, ceiling, 0) == FAILURE)
			{
				free(ceiling);
				return (FAILURE);
			}
			free(ceiling);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	sprites_information(t_data *data)
{
	if (search_sprites(data) == FAILURE)
		return (FAILURE);
	if (data->n_sprite == NULL || data->s_sprite == NULL
		|| data->w_sprite == NULL || data->e_sprite == NULL)
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
		return (err_msg(NULL, RGB1, FAILURE));
	if (ceiling_information(data) == FAILURE)
		return (err_msg(NULL, RGB2, FAILURE));
	if (sprites_information(data) == FAILURE)
		return (err_msg(NULL, SPRITE, FAILURE));
	if (map_information(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


