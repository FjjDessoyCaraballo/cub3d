/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:10:33 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/11 11:50:23 by araveala         ###   ########.fr       */
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
