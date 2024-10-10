/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:28:52 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/10 11:28:54 by fdessoy-         ###   ########.fr       */
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
/**
 * `check_rgb_range()` will check if the metadata that we gathered from
 * the file are within the range of `0` to `255`. They're all variables of
 * type `size_t` so we do not need to check for negative numbers.
 * 
 * @param data check_rgb_range() works with only one variable, which is the
 * data struct for checking the variables.
 * 
 * @return this function returns only SUCCESS or FAILURE upon checking the
 * variables in our struct. If the numbers are out of bound, we return 
 * FAILURE and output a helpful error message for the user.
 */
static int8_t	check_rgb_range(t_data *data)
{
	if ((data->f_red > 255)
		|| (data->f_green > 255)
		|| (data->f_blue > 255)
		|| (data->c_red > 255)
		|| (data->c_green > 255)
		|| (data->c_blue > 255))
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
	if (array[3])
	{
		free_array(array);
		return (FAILURE);
	}
	if (rgb_assignment(data, array, flag) == FAILURE)
	{
		free_array(array);
		return (FAILURE);
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

/** `rgb_parse()` will find the element that contains the letter
 * "C" or "F" in the very first position of the string. The subject
 * of our project states clearly that the very first information that
 * will be displayed will be these letters for the RGB scheme.
 * 
 * The RGB variables will be use for the floor (F) and for the ceiling
 * (C), and only accepts positive numbers within the range of 0 to 255.
 * 
 * @param data Our data struct which stores most of the metadata from
 * the document;
 * @param str At this point, rgb_parse() already has the string that
 * matches the regular expression expected from the user;
 * @param flag We use a `int flag` in this function to differentiate if 
 * we are dealing with ceiling or floor, this way we can use the same
 * function for both and not build extra functions later to deal with 
 * assignment for different parts of the struct;
 * 
 * @return our return value will be `SUCCESS` or `FAILURE` depending
 * on the file that the user gives us. If the file contains digits that
 * are within the estipulated bounds, rgb_parse() returns `SUCCESS`.
 * Otherwise, we return `FAILURE`.
 */
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