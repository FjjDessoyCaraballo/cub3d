/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:01:18 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/06 18:32:46 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	is_rgb_ok(char **info)
{
	int	i;

	i = 0;
	while (info[i])
		i++;
	if (i != 2)
		return (err_msg(NULL, RGB8, FAILURE));
	return (SUCCESS);
}

int8_t	rgb_parse2(t_data *data, char **info, int flag)
{
	int	index;

	index = 0;
	if (is_rgb_ok(info) == FAILURE)
		return (FAILURE);
	while (info[index])
	{
		if (!ft_strncmp(info[index], "C", 1)
			|| !ft_strncmp(info[index], "F", 1))
			index++;
		if (separate_rgb(data, info[index], flag) == FAILURE)
			return (FAILURE);
		index++;
	}
	return (SUCCESS);
}
