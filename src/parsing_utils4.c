/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:54:31 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/06 15:32:09 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

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

int8_t	repeated_rgb(char **file)
{
	int	i;
	int	repeat_c;
	int	repeat_f;

	i = 0;
	repeat_c = 0;
	repeat_f = 0;
	while (file[i])
	{
		if (file[i][0] == 'C')
			repeat_c++;
		if (file[i][0] == 'F')
			repeat_f++;
		i++;
	}
	if (repeat_f != 1)
		return (err_msg(NULL, RGB3, FAILURE));
	if (repeat_c != 1)
		return (err_msg(NULL, RGB4, FAILURE));
	return (SUCCESS);
}

static int8_t	insanity(char *rgb)
{
	int	i;
	int	repeat_c;
	int repeat_f;

	i = 0;
	repeat_c = 0;
	repeat_f = 0;
	while (rgb[i])
	{
		if (rgb[i] == 'C')
			repeat_c++;
		if (rgb[i] == 'F')
			repeat_f++;
		i++;
	}
	if (repeat_c > 0 && repeat_f > 0)
		return (err_msg(NULL, RGB5, FAILURE));
	else if (repeat_f > 1 || repeat_c > 1)
		return (err_msg(NULL, RGB5, FAILURE));
	return (SUCCESS);
}

int8_t	repeated_inline(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i][0] == 'C' || file[i][0] == 'F')
		{
			if (insanity(file[i]) == FAILURE)
				return (err_msg(NULL, RGB5, FAILURE));
		}
		i++;
	}
	return (SUCCESS);
}

/** In extra_info() we are going to parse out edge cases.
 * we first check if there is extra information in the string,
 * then we go on
 */
int8_t	extra_info(char *rgb)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(rgb, ',');
	if (!array)
		return (err_msg(NULL, MALLOC, FAILURE));
	while (array[i])
		i++;
	if (i > 3)
	{
		free_array(array);
		return (err_msg(NULL, RGB5, FAILURE));
	}
	free_array(array);
	return (SUCCESS);
}
