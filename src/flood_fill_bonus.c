/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:28:52 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/14 15:02:10 by fdessoy-         ###   ########.fr       */
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
		if (!data->mp_cpy[i])
			return (err_msg(NULL, MALLOC, FAILURE));
		i++;
	}
	return (SUCCESS);
}

void	flood_fill(t_data *data, size_t y, size_t x)
{
	if (y == 0 || x == 0 || data->mp_cpy[y][x] == '1'
		|| data->mp_cpy[y][x] == 'x'
		|| data->mp_cpy[y][x] == 'D')
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

static int8_t	between_rooms(t_data *data, char **map, int i, int j)
{
	if (i != 0 || i != data->map_y || j != data->map_x || j != 0)
	{
		if ((map[i + 1][j] == '0' && map[i - 1][j] == '0'
			&& map[i][j + 1] == '1' && map[i][j - 1] == '1')
			|| (map[i][j + 1] == '0' && map[i][j - 1] == '0'
			&& map[i + 1][j] == '1' && map[i - 1][j] == '1'))
		{
			data->dpos_x = j;
			data->dpos_y = i;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

/**
 * Here we are checking if our bonus door exists. As we check
 * for its existence, we also extract its position and check if
 * adjacent positions are 0's and 1's, which means that the door
 * is positioned between rooms; the aforementioned test is done
 * to be sure that the door is not positioned at the limits of
 * the map and to avoid out of boundaries reads.
 * 
 * @param map our map that is located in the `.cub` file
 * 
 * @param i row index
 * 
 * @param j column index
 * 
 * @return if the door is correctly positioned by the player,
 * we return `SUCCCESS`, which means that we also stored the
 * position of the door. In case the door was wrongly positioned
 * we return `FAILURE`.
 */
int8_t	door_exists(t_data *data, int i, int j)
{
	int	flag;

	flag = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				if (between_rooms(data, data->map, i, j) == FAILURE)
					return (err_msg(NULL, BONUS, FAILURE));
				data->map[i][j] = '1';
				flag++;
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (err_msg(NULL, BONUS, FAILURE));
	return (SUCCESS);
}
