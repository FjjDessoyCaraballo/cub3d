/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:50 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 12:30:00 by fdessoy-         ###   ########.fr       */
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