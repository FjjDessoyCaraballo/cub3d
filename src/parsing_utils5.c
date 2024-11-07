/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:01:18 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/07 14:14:47 by fdessoy-         ###   ########.fr       */
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
/**
 * `is_file()` checks for files that can be read and if they even
 * exist in the first place. If the file exists and is readable, we
 * return `SUCCESS`.
 * 
 * @param fname file that you want to check;
 * 
 * @return `SUCCESS` upon successful completion and `FAILURE` if the
 * file does not have permissions/does not exist.
 */
static int8_t	is_file(char *fname)
{
	int	fd;

	fd = open(fname, R_OK);
	if (fd >= 0)
	{
		close(fd);
		return (SUCCESS);
	}
	close(fd);
	return (FAILURE);
}

int8_t	is_png(char *sprite)
{
	if (is_dir(sprite) == FAILURE)
		return (err_msg(NULL, SPRITE4, FAILURE));
	if (check_suffix(ft_strrchr(sprite, '/'), \
		".png", 4) == FAILURE)
		return (err_msg(NULL, SPRITE3, FAILURE));
	if (is_file(sprite) == FAILURE)
		return (err_msg(NULL, SPRITE, FAILURE));
	return (SUCCESS);
}
