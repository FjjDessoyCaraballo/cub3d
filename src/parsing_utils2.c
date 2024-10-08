/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:08:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/08 15:34:55 by fdessoy-         ###   ########.fr       */
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