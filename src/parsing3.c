/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:12:41 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/21 12:29:49 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	no_sprite(t_data *data, int index)
{
	static char		**sprite;

	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "N", 1)
			&& !ft_strncmp(&data->file[index][1], "O", 1)
			&& !ft_strncmp(&data->file[index][2], " ", 1))
		{
			sprite = ft_split(data->file[index], ' ');
			if (!sprite)
				return (FAILURE);
			data->n_sprite = extract_sprite(sprite);
			if (!data->n_sprite)
			{
				free_array(sprite);
				return (err_msg(NULL, "Error\nMissing sprite\n", FAILURE));
			}
			free_array(sprite);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	so_sprite(t_data *data, int index)
{
	static char		**sprite;

	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "S", 1)
			&& !ft_strncmp(&data->file[index][1], "O", 1)
			&& !ft_strncmp(&data->file[index][2], " ", 1))
		{
			sprite = ft_split(data->file[index], ' ');
			if (!sprite)
				return (FAILURE);
			data->s_sprite = extract_sprite(sprite);
			if (!data->s_sprite)
			{
				free_array(sprite);
				return (err_msg(NULL, "Error\nMissing sprite\n", FAILURE));
			}
			free_array(sprite);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	we_sprite(t_data *data, int index)
{
	static char		**sprite;

	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "W", 1)
			&& !ft_strncmp(&data->file[index][1], "E", 1)
			&& !ft_strncmp(&data->file[index][2], " ", 1))
		{
			sprite = ft_split(data->file[index], ' ');
			if (!sprite)
				return (FAILURE);
			data->w_sprite = extract_sprite(sprite);
			if (!data->w_sprite)
			{
				free_array(sprite);
				return (err_msg(NULL, "Error\nMissing sprite\n", FAILURE));
			}
			free_array(sprite);
		}
		index++;
	}
	return (SUCCESS);
}

static int8_t	ea_sprite(t_data *data, int index)
{
	static char		**sprite;

	while (data->file[index])
	{
		if (!ft_strncmp(&data->file[index][0], "E", 1)
			&& !ft_strncmp(&data->file[index][1], "A", 1)
			&& !ft_strncmp(&data->file[index][2], " ", 1))
		{
			sprite = ft_split(data->file[index], ' ');
			if (!sprite)
				return (FAILURE);
			data->e_sprite = extract_sprite(sprite);
			if (!data->e_sprite)
			{
				free_array(sprite);
				return (err_msg(NULL, "Error\nMissing sprite\n", FAILURE));
			}
			free_array(sprite);
		}
		index++;
	}
	return (SUCCESS);
}

/**
 * `search_sprites()` is mainly separated from the rest of the parsing
 * just for memory management. Given the repetitive nature, it is possible
 * to observe plainly that it does the same task with few differences:
 * 
 * 1. `no_sprite()` takes the north wall texture.
 * 2. `so_sprite()` takes the south wall texture.
 * 3. `we_sprite()` takes the west wall texture.
 * 4. `ea_sprite()` takes the east wall texture.
 * 
 * All these functions are saving the whole strings that are found in the
 * `.cub` file and parse out the empty spaces leaving only the path to the
 * sprite given by the file. The repetitive nature was a design choice to be
 * able to manage the memory in case `malloc()` fails at any point, since we 
 * extract the information using `ft_strdup()`.
 * 
 * Upon successful extraction of all string, we simply return `SUCCESS` to the
 * caller function. All the information has been saved in the `t_data` struct.
 * 
 * This part of the code DOES NOT take care of checking if the path if 
 * valid or not. That will be taken care by the MLX functions later on.
 */
int8_t	search_sprites(t_data *data)
{
	if (extra_sprite(data->file, "NO ", 0) == FAILURE
		|| extra_sprite(data->file, "SO ", 0) == FAILURE
		|| extra_sprite(data->file, "EA ", 0) == FAILURE
		|| extra_sprite(data->file, "WE ", 0) == FAILURE)
		return (FAILURE);
	if (no_sprite(data, 0) == FAILURE
		|| ea_sprite(data, 0) == FAILURE
		|| so_sprite(data, 0) == FAILURE
		|| we_sprite(data, 0) == FAILURE)
		return (FAILURE);
	if (!data->n_sprite || !data->e_sprite
		|| !data->s_sprite || !data->w_sprite)
		return (err_msg(NULL, "Error\ncheck formats in cub file", FAILURE));
	remove_nl(data->n_sprite);
	remove_nl(data->w_sprite);
	remove_nl(data->s_sprite);
	remove_nl(data->e_sprite);
	if (is_png(data->n_sprite) == FAILURE
		|| is_png(data->s_sprite) == FAILURE
		|| is_png(data->w_sprite) == FAILURE
		|| is_png(data->e_sprite) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
