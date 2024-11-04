/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:54:31 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/04 14:45:33 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	extra_rgb(char **rgb, int flag)
{
	int	i;
	int	repeat;

	i = 0;
	repeat = 0;
	while (rgb[i])
	{
		if (!ft_strncmp(rgb[i], "C", 1)
			|| !ft_strncmp(rgb[i], "F", 1))
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

void	remove_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}
