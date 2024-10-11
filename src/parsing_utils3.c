/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:18:23 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 10:24:34 by fdessoy-         ###   ########.fr       */
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

