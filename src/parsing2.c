/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:05 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/07 15:25:30 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	parse_out_space(char *str)
{
	(void)str;
	return (0);
}

static int8_t	cf_information(t_data *data)
{
	int	index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "F", 1))
			data->floor_info = ft_strdup(data->file[index]);
		if (!ft_strncmp(&data->file[index][0], "C", 1))
			data->ceiling_info = ft_strdup(data->file[index]);
		index++;
	}
	return (SUCCESS);
}

static int8_t	sprites_information(t_data *data)
{
	int			index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "N", 1)
			&& !ft_strncmp(&data->file[index][1], "O", 1))
		{
			parse_out_space(data->file[index]);
			data->n_sprite = ft_strdup(data->file[index]);
		}
		index++;
	}	
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
	if (cf_information(data) == FAILURE)
		return (FAILURE);
	if (sprites_information(data) == FAILURE)
		return (FAILURE);
	if (map_information(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
