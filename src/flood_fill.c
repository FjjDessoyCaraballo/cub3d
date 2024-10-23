/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:28:52 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/23 15:08:42 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	check_if_walled(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->mp_cpy[i])
	{
		j = 0;
		while (data->mp_cpy[i][j])
		{
			if (data->mp_cpy[i][j] == '0')
				flood_fill(data, i, j);
			j++;
		}
		if (data->broken_map == true)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int8_t	copy_map(t_data *data)
{
	int	i;

	i = 0;
	data->mp_cpy = ft_calloc((data->map_length + 1), sizeof(char *));
	if (!data->mp_cpy)
		return (err_msg(NULL, MALLOC, FAILURE));
	while (data->map[i])
	{
		data->mp_cpy[i] = ft_strdup(data->map[i]);
		i++;
	}
	return (SUCCESS);
}

void	flood_fill(t_data *data, size_t y, size_t x)
{
	if (y == 0 || x == 0 || data->mp_cpy[y][x] == '1'
		|| data->mp_cpy[y][x] == 'x') 
		return ;
	if (data->mp_cpy[y][x + 1] == '\0'
		|| data->mp_cpy[y][x - 1] == '\0'
		|| data->mp_cpy[y + 1][x] == '\0'
		|| data->mp_cpy[y - 1][x] == '\0')
	{
		data->broken_map = true;
		return ;
	}
	data->mp_cpy[y][x] = 'x';
	flood_fill(data, y + 1, x);
	flood_fill(data, y, x + 1);
	flood_fill(data, y - 1, x);
	flood_fill(data, y, x - 1);
}
