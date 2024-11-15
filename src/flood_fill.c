/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:28:52 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/15 18:11:49 by araveala         ###   ########.fr       */
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
			if (data->mp_cpy[i][j] == '0' && (i == 0 || j == 0
				|| i == data->map_length || j == data->map_width))
				return (FAILURE);
			if (data->mp_cpy[i][j] == '0' && i != 0 && j != 0 
				&& i != data->map_length && j != data->map_width)
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
		int x = 0;
		while (data->mp_cpy[i][x])
		{
			if (data->mp_cpy[i][x  + 1] == '\n')
				printf("next one is nl x = %d\n", x);

			if (data->mp_cpy[i][x  + 1] == '\0')
				printf("next one is terminator x = %d\n", x);
			x++;
		}
		if (!data->mp_cpy[i])
			return (err_msg(NULL, MALLOC, FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	saftey_check(t_data *data, size_t y, size_t x)
{
	int flag1;
	int	flag2;

	flag1 = 0;
	flag2 = 0;
	if (y > 0 && data->mp_cpy[y] && x > ft_strlen(data->mp_cpy[y - 1]))
		flag1 = 1;
	if ((int)y > data->map_length && data->mp_cpy[y] && ft_strlen(data->mp_cpy[y + 1]) > ft_strlen(data->mp_cpy[y]))
		flag2 = 1;
//	if (data->mp_cpy[y] && data->mp_cpy[y][x] == '0' && (flag1 == 1 || flag2 == 1))
//	{
//		data->broken_map = true;
//		return (FAILURE);
//	}
	if (y == 0 || x == 0 || data->mp_cpy[y][x] == '1'
		|| data->mp_cpy[y][x] == 'x')
		return (FAILURE);
	if ((data->mp_cpy[y] && data->mp_cpy[y][x] == '0' && (flag1 == 1 || flag2 == 1))
		|| data->mp_cpy[y][x + 1] == '\0'
		|| data->mp_cpy[y][x - 1] == '\0'
		|| (flag2 == 1 && data->mp_cpy[y + 1][x] == '\0')
		|| data->mp_cpy[y + 1] == NULL
		|| (flag1 == 1 && data->mp_cpy[y - 1][x] == '\0'))
	{
		data->broken_map = true;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	flood_fill(t_data *data, size_t y, size_t x)
{
	if (x > ft_strlen(data->mp_cpy[y]))
		return ;
	if (saftey_check(data, y, x) == FAILURE)
		return ;
	data->mp_cpy[y][x] = 'x';
	if ((int)y < data->map_length && data->mp_cpy[y] && ft_strlen(data->mp_cpy[y + 1]) <= ft_strlen(data->mp_cpy[y]))
		flood_fill(data, y + 1, x);
	if (x <= ft_strlen(data->mp_cpy[y]))
		flood_fill(data, y, x + 1);
	if (y > 0 && data->mp_cpy[y] && ft_strlen(data->mp_cpy[y - 1]) > ft_strlen(data->mp_cpy[y]))
		flood_fill(data, y - 1, x);
	if (x >= 0)
		flood_fill(data, y, x - 1);
}
