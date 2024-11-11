/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:08:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/11 13:12:36 by fdessoy-         ###   ########.fr       */
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
				return (err_msg(NULL, RGB5, FAILURE));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int8_t	rgb_assignment(t_data *data, char **array, int flag)
{
	if (!array[0] || !array[1] || !array[2])
		return (err_msg(NULL, "Error\nBroken RGB\n", FAILURE));
	if (only_number_check(array) == FAILURE)
		return (FAILURE);
	if (array[2][0] == '\n')
		return (err_msg(NULL, "Error\nBroken RGB\n", FAILURE));
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
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != '1' && str[i] != '0'
				&& str[i] != 'N' && str[i] != 'S' && str[i] != 'W'
				&& str[i] != 'E' && str[i] != '\n' && str[i] != '\t')
				return (FAILURE);
			i++;
		}
		return (SUCCESS);
	}
	else
		return (SUCCESS);
}

int8_t	allocate_mapmem(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i])
		i++;
	data->map_end = i;
	i = 0;
	while (data->file[i])
	{
		if (is_map(data->file[i]) == SUCCESS
			&& only_nl(data->file[i]) == SUCCESS)
		{
			data->map_start = i;
			break ;
		}
		i++;
	}
	data->map_length = data->map_end - data->map_start;
	data->map = ft_calloc((data->map_length + 1), sizeof(char *));
	if (!data->map)
		return (FAILURE);
	return (SUCCESS);
}

void	rem_map_nl(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = '\0';
			j++;
		}
		i++;
	}
}
