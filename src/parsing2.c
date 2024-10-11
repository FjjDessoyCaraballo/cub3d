/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:05 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 11:37:11 by fdessoy-         ###   ########.fr       */
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

// FOCUS HERE: our map is parsing out lines of the map that have extra characters
static int8_t	map_information(t_data *data)
{
	int	i;
	int	j;

	if (allocate_mapmem(data) == FAILURE)
		return (err_msg(NULL, MALLOC, FAILURE));
	i = data->map_start;
	j = 0;
	while(i <= data->map_end - 1)
	{
		if (is_map(data->file[i]) == SUCCESS
			&& only_nl(data->file[i]) == SUCCESS)
		{
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j])
				return (err_msg(NULL, MALLOC, FAILURE));
			j++;
		}
		i++;
	}
	data->map[j] = '\0';
	return (SUCCESS);
}

/**
 * `extract()` deals with extracting the metadata from the `.cub` file.
 * We do so with four different functions:
 * 
 * `floor_information(t_data *data)` we search for the string 
 * "F 255,255,255" within the `.cub` file;
 * 
 * `ceiling_information(t_data *data)` same as floor_information() but
 * we search for the string "C 255,255,255";
 * 
 * `sprites_information(t_data *data)` here we are taking the four
 * strings that contain the paths to the sprites of the walls textures;
 * 
 * `map_information(t_data *data)` here we extract the metadata of the
 * map. The map should consists of only `1`, `0`, and the player character
 * (`N`, `S`, `E` or `W`). The map does not need to be rectangular.
 * 
 * @param data `extract()` takes only the data struct as a parameter.
 * 
 * @return if any of the metadata is corrupted/incorrect, `extract()`
 * will return `FAILURE` before proceeding to extract any more data. Upon
 * successful extraction, the function will return `SUCCESS`.
 */
int8_t	extract(t_data *data)
{
	if (floor_information(data) == FAILURE)
		return (err_msg(NULL, RGB2, FAILURE));
	if (ceiling_information(data) == FAILURE)
		return (err_msg(NULL, RGB1, FAILURE));
	if (sprites_information(data) == FAILURE)
		return (err_msg(NULL, SPRITE, FAILURE));
	if (map_information(data) == FAILURE)
		return (FAILURE);
	remove_nl(data->map);
	if (check_original_length(data) == FAILURE)
		return (FAILURE);
	if (player_exists(data, data->map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


