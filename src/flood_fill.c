/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:28:52 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 13:28:30 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

// int8_t	copy_map(t_data *data)
// {
// 	data->c_red = 0;
// 	return (SUCCESS);
// }

// void	flood_fill(char **map, int y, int x)
// {
// 	if (map[y][x] == '1' || map[y][x] == 'x')
// 		return ;
// 	map[y][x] = 'x';
// 	flood_fill(map, y + 1, x);
// 	flood_fill(map, y, x + 1);
// 	flood_fill(map, y - 1, x);
// 	flood_fill(map, y, x - 1);
// }