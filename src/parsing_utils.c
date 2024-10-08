/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:50 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 14:45:33 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * At this point, we should get strings in the following format:
 * 
 * NO ./path_to_the_north_texture
 * SO ./path_to_the_south_texture
 * WE ./path_to_the_west_texture
 * EA ./path_to_the_east_texture
 * 
 * It is possible that the user may insert extra spaces between elements,
 * therefore we need to jump over them. We can always assume that the first
 * two elements of the string will be the `type identifier` because of the
 * subject wording. That considered, we may jump two positions and start 
 * looking for any ascii value that we will consider to be our map.
 */
char	*sprite_path(char *str)
{
	int		index;

	index = 3;
	while (str[index])
	{
		if (str[index] >= 1 && str[index] <= 32)
			index++;
		else
			return (&str[index]);
	}
	return (NULL);
}

static int8_t	check_rgb_range(t_data *data)
{
	if ((data->f_red < 0 || data->f_red > 255)
		|| (data->f_green < 0 || data->f_green > 255)
		|| (data->f_blue < 0 || data->f_blue > 255)
		|| (data->c_red < 0 || data->c_red > 255)
		|| (data->c_green < 0 || data->c_green > 255)
		|| (data->c_blue < 0 || data->c_blue > 255))
		return (FAILURE);
	return (SUCCESS);
}

/**
 * break_commas() receives the rgb_str string of numbers with commas
 * and it breaks it down into just the numbers converted from ascii
 * to integers. Before calling this function, there is a hard-coded
 * flag to identify if the RGB numbers are intended for the ceiling
 * or floor.
 */
static int8_t	break_commas(t_data *data, char *rgb_str, int flag)
{
	static char **array;

	array = ft_split(rgb_str, ',');
	if (!array)
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
	free_array(array);
	if (check_rgb_range(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/* This function is here just to save lines from rgb_parse */
static int8_t	separate_rgb(t_data *data, char *str, int flag)
{
	char	*rgb;
	
	rgb = ft_strdup(str);
	if (!rgb)
		return (FAILURE);
	if (break_commas(data, rgb, flag) == FAILURE)
	{
		free(rgb);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	rgb_parse(t_data *data, char *str, int flag)
{
	char	**info;
	int		index;

	info = ft_split(str, ' ');
	if (!info)
		return (FAILURE);
	index = 0;
	while (info[index])
	{
		if (!ft_strncmp(info[index], "C", 1)
			|| !ft_strncmp(info[index], "F", 1))
			index++;
		if (separate_rgb(data, info[index], flag) == FAILURE)
		{
			free_array(info);
			return (FAILURE);
		}
		index++;
	}
	free_array(info);
	return (SUCCESS);
}