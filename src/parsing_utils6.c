/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:10:33 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/29 12:58:43 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

char	*extract_sprite(char **sprite)
{
	int	i;

	i = 0;
	while (sprite[i])
		i++;
	if (i > 2)
		return (NULL);
	i = 0;
	while (sprite[i])
	{
		if (!ft_strncmp(sprite[i], "NO", 2)
			|| !ft_strncmp(sprite[i], "EA", 2)
			|| !ft_strncmp(sprite[i], "SO", 2)
			|| !ft_strncmp(sprite[i], "WE", 2))
		{
			i++;
			return (ft_strdup(sprite[i]));
		}
		i++;
	}
	return (NULL);
}

static int8_t	insert_space(t_data *data, int index)
{
	char	*new_line;
	int		orig_len;
	int		i;

	orig_len = ft_strlen(data->map[index]);
	new_line = malloc(data->map_width + 1);
	if (!new_line)
		return (err_msg(NULL, MALLOC, FAILURE));
	i = 0;
	while (i < orig_len)
	{
		new_line[i] = data->map[index][i];
		i++;
	}
	while (i < data->map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	free(data->map[index]);
	data->map[index] = new_line;
	return (SUCCESS);
}

int8_t	fill_space(t_data *data)
{
	int	i;
	int	line_len;

	i = 0;
	if (!data->map[i])
		return (err_msg(NULL, MAP1, FAILURE));
	line_len = ft_strlen(data->map[i]);
	while (data->map[i])
	{
		if (line_len < data->map_width)
		{
			if (insert_space(data, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int8_t	extra_sprite(char **file, char *cardinal, int index)
{
	int8_t	repeat;

	repeat = 0;
	while (file[index])
	{
		if (!ft_strncmp(&file[index][0], &cardinal[0], 1)
			&& !ft_strncmp(&file[index][1], &cardinal[1], 1)
			&& !ft_strncmp(&file[index][2], &cardinal[2], 1))
		{
			repeat++;
			if (repeat > 1)
				return (err_msg(NULL, SPRITE2, FAILURE));
		}
		index++;
	}
	return (SUCCESS);
}
