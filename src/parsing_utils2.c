/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:08:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/10 10:44:28 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	only_number_check(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\n')
				break ;
			if (!ft_isdigit(array[i][j]))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int8_t	rgb_assignment(t_data *data, char **array, int flag)
{
	if (only_number_check(array) == FAILURE)
		return (FAILURE);
	if (flag == 1)
	{
		data->c_red = ft_atoi(array[0]);
		data->c_green = ft_atoi(array[1]);
		data->c_blue = ft_atoi(array[2]);	
	}
	else
	{
		data->f_red = ft_atoi(array[0]);
		data->f_green = ft_atoi(array[1]);
		data->f_blue = ft_atoi(array[2]);	
	}
	return (SUCCESS);
}

int8_t	is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'W'
			&& str[i] != 'E' && str[i] != '\n' && str[i] != '\t')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int8_t	allocate_mapmem(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i])
	{
		if (is_map(data->file[i]) == SUCCESS)
		{
			data->map_length++;
			if (ft_strlen(data->file[i]) > data->map_width)
				data->map_width = ft_strlen(data->file[i]);
		}
		i++;
	}
	data->map = ft_calloc(data->map_length + 1, sizeof(char *));
	if (!data->map)
		return (FAILURE);
	return (SUCCESS);
}


// DEPRECATED
// int8_t	check_element(char *map_line)
// {
// 	if (!ft_strncmp(&map_line[0], "C", 1) || !ft_strncmp(&map_line[0], "F", 1)
// 		|| (!ft_strncmp(&map_line[0], "N", 1) && ft_strncmp(&map_line[1], "O", 1))
// 		|| (!ft_strncmp(&map_line[0], "S", 1) && ft_strncmp(&map_line[1], "O", 1))
// 		|| (!ft_strncmp(&map_line[0], "W", 1) && ft_strncmp(&map_line[1], "E", 1))
// 		|| (!ft_strncmp(&map_line[0], "E", 1) && ft_strncmp(&map_line[1], "A", 1)))
// 		return (FAILURE);
// 	return (SUCCESS);
// }