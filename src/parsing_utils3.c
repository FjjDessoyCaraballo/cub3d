/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:18:23 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/29 10:40:47 by fdessoy-         ###   ########.fr       */
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
	{
		data->n_player = true;
		data->p_dir_y = -1;
	}
	else if (dir == 'S')
	{
		data->s_player = true;
		data->p_dir_y = 1;
	}
	else if (dir == 'W')
	{
		data->w_player = true;
		data->p_dir_x = -1;
	}
	else if (dir == 'E')
	{
		data->e_player = true;
		data->p_dir_x = 1;
	}
	data->y_ppos = row;
	data->x_ppos = col;
}

int8_t	player_exists(t_data *data, char **map, int player)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W') && j != 0 && i != 0
				&& i != data->map_length && j != data->map_width)
			{
				p_pos(data, map[i][j], i, j);
				map[i][j] = '0';
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
	int	i;

	i = 0;
	while (data->map[i])
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
