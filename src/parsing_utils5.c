/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:01:18 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/21 12:20:29 by fdessoy-         ###   ########.fr       */
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
	int		fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (FAILURE);
	}
	if (read(fd, &fname, 0) <= 0)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

/**
 * `is_png()` parses out the texture informed by user. The first
 * check is if the file is a directory instead of a normal file;
 * the second check is for the correct `.png` suffix; the final
 * check is to see if the file exists.
 * 
 * @param sprite the function takes only the path of the texture;
 * 
 * @return if all the checks are successful, we return `SUCCESS`.
 * Otherwise, we return `FAILURE`.
 */
int8_t	is_png(char *sprite)
{
	if (is_dir(sprite) == FAILURE)
		return (err_msg(NULL, SPRITE4, FAILURE));
	if (!ft_strrchr(sprite, '/'))
		return (err_msg(NULL, SPRITE, FAILURE));
	if (check_suffix(ft_strrchr(sprite, '/'), \
		".png", 4) == FAILURE)
		return (err_msg(NULL, SPRITE3, FAILURE));
	if (is_file(sprite) == FAILURE)
		return (err_msg(NULL, SPRITE, FAILURE));
	return (SUCCESS);
}
