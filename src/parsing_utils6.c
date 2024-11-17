/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:10:33 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/17 15:11:05 by fdessoy-         ###   ########.fr       */
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

// static int8_t	insert_space(t_data *data, int index)
// {
// 	char	*new_line;
// 	int		i;

// 	i = 0;
// 	new_line = malloc(data->map_width + 1);
// 	if (!new_line)
// 		return (err_msg(NULL, MALLOC, FAILURE));
// 	ft_strlcpy(new_line, data->map[index], ft_strlen(data->map[index]));
// 	while (i < data->map_width)
// 		new_line[i++] = ' ';
// 	new_line[i] = '\0';
// 	free(data->map[index]);
// 	data->map[index] = ft_strdup(new_line);
// 	if (!data->map[index])
// 	{
// 		free(new_line);
// 		return (err_msg(NULL, MALLOC, FAILURE));
// 	}
// 	free(new_line);
// 	return (SUCCESS);
// }

static int8_t	insert_space(t_data *data, int index)
{
	char	*new_line;
	int		orig_len;
	int		i;

	orig_len = ft_strlen(data->map[index]);
	new_line = malloc(data->map_width + 1); // Allocate memory for the full width + null terminator.
	if (!new_line)
		return (err_msg(NULL, MALLOC, FAILURE));
	
	// Copy the original string into the new line.
	i = 0;
	while (i < orig_len)
	{
		new_line[i] = data->map[index][i];
		i++;
	}

	// Fill the rest with spaces.
	while (i < data->map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0'; // Null-terminate the string.

	// Replace the old line with the new one.
	free(data->map[index]);
	data->map[index] = new_line; // Directly assign the new line.
	
	return (SUCCESS);
}


int8_t	fill_space(t_data *data)
{
	int	i;
	int	line_len;

	i = 0;
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