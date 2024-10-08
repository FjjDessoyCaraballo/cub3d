/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:12:41 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 10:18:26 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"

static int8_t	no_sprite(t_data *data)
{
	int			index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "N", 1)
			&& !ft_strncmp(&data->file[index][1], "O", 1))
		{
			data->n_sprite = ft_strdup(data->file[index]);
			if (!data->n_sprite)
				return (FAILURE);
			parse_out_space(data->file[index]);
		}
		index++;
	}
}
static int8_t	so_sprite(t_data *data)
{
	int			index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "S", 1)
			&& !ft_strncmp(&data->file[index][1], "O", 1))
		{
			data->s_sprite = ft_strdup(data->file[index]);
			if (!data->s_sprite)
				return (FAILURE);
			parse_out_space(data->file[index]);
		}
		index++;
	}
}
static int8_t	we_sprite(t_data *data)
{
	int			index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "W", 1)
			&& !ft_strncmp(&data->file[index][1], "E", 1))
		{
			data->w_sprite = ft_strdup(data->file[index]);
			if (!data->w_sprite)
				return (FAILURE);
			parse_out_space(data->file[index]);
		}
		index++;
	}
}
static int8_t	ea_sprite(t_data *data)
{
	int			index;

	index = 0;
	while(data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "E", 1)
			&& !ft_strncmp(&data->file[index][1], "A", 1))
		{
			data->e_sprite = ft_strdup(data->file[index]);
			if (!data->e_sprite)
				return (FAILURE);
			parse_out_space(data->file[index]);
		}
		index++;
	}	
}

int8_t	search_sprites(t_data *data)
{
	if (no_sprite(data) == FAILURE)
		return (FAILURE);
	if (so_sprite(data) == FAILURE)
	{
		free(data->n_sprite);
		return (FAILURE);
	}
	if (we_sprite(data) == FAILURE)
	{
		free(data->n_sprite);
		free(data->s_sprite);
		return (FAILURE);
	}
	if (ea_sprite(data) == FAILURE)
	{
		free(data->n_sprite);
		free(data->s_sprite);
		free(data->w_sprite);
		return (FAILURE);
	}
	return (SUCCESS);
}