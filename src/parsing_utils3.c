/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:18:23 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/17 14:09:33 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	only_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n' && str[i + 1] == '\0')
		return (FAILURE);
	return (SUCCESS);
}
static void	p_pos(t_data *data, char dir, int row, int col)
{
	if (dir == 'N')
		data->n_player = true;
	else if (dir == 'S')
		data->s_player = true;
	else if (dir == 'W')
		data->w_player = true;
	else if (dir == 'E')
		data->e_player = true;
	data->y_ppos = row;
	data->x_ppos = col;
}

int8_t	player_exists(t_data *data, char **map)
{
	int		i;
	int		j;
	int		player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				p_pos(data, map[i][j], i, j);
				player++;
			}
			j++;
		}
		i++;
	}
	if (player != 1)
		return (err_msg(NULL, PLAYER, FAILURE));
	return (SUCCESS);
}

int8_t	check_original_length(t_data *data)
{
//	size_t	i;
	int i;
	i = 0;
	while(data->map[i])
		i++;
	if (i != data->map_length)
		return (err_msg(NULL, BRK_MAP, FAILURE));
	return (SUCCESS);
}

uint8_t	get_width(char **map)
{
	int				i;
	unsigned int	width;

	i = 0;
	width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

int8_t	extra_rgb(char **rgb, int flag)
{
	int	i;
	int	repeat;

	i = 0;
	repeat = 0;
	while (rgb[i])
	{
		if (!ft_strncmp(rgb[i], "C", 1)
			|| !ft_strncmp(rgb[i] , "F", 1))
			repeat++;
		i++;
	}
	if (repeat != 1)
	{
		if (flag == 0)
			return (err_msg(NULL, RGB4, FAILURE));
		else
			return (err_msg(NULL, RGB3, FAILURE));
	}
	return (SUCCESS);
}