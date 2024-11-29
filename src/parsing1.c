/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:45:25 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/29 12:42:47 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	is_dir(char *fname)
{
	int	fd;

	fd = open(fname, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

/** `check_name()` will check for suffixes of files. If it doesn't
 * find the comma to begin, it automatically discards the string
 * and returns `FAILURE`. If it finds at least one comma, it will
 * check if its equivalent to the set target. In our case, it will
 * check for `.cub` files.
 * 
 * @param fname filename which you're looking for a suffix string;
 * 
 * @param target target suffix string;
 * 
 * @param size specific size of the suffix string;
 * 
 * @return Returns `SUCCESS` upon completion, which means that the
 * `fname` contains the `target` suffix. Otherwise, it returns 
 * `FAILURE`
 */
int8_t	check_suffix(char *fname, char *target, int size)
{
	char	*str;

	if (!ft_strrchr(fname, '.'))
		return (err_msg(NULL, NAME, FAILURE));
	str = ft_strrchr(fname, '.');
	if (ft_strncmp(str, target, size))
		return (err_msg(NULL, NAME, FAILURE));
	return (SUCCESS);
}

static int32_t	count_lines(int fd)
{
	int		i;
	char	*line;

	if (fd < 0)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static int8_t	open_file(t_data *data, char *fname)
{
	int	fd;
	int	i;

	if (is_dir(fname) == FAILURE)
		return (err_msg(NULL, DIR, FAILURE));
	data->file_len = count_lines(open(fname, O_RDONLY));
	if (data->file_len == -1)
		return (err_msg(NULL, OPEN, FAILURE));
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (err_msg(NULL, OPEN, FAILURE));
	data->file = ft_calloc(data->file_len + 1, sizeof(char *));
	if (!data->file)
	{
		close(fd);
		return (err_msg(NULL, MALLOC, FAILURE));
	}
	i = 0;
	while (i < data->file_len)
		data->file[i++] = get_next_line(fd);
	close(fd);
	return (SUCCESS);
}

/** Here we are parsing out the file and checking for possible
 * user errors. In check_name() we make sure that the first and 
 * only argument will be the <filename> and it contains the suffix
 * `.cub`. If this check faills, we free the struct and exit with
 * costumized message. In open_file() we want to extract the file
 * and we do more checks, such as user inputting directories that 
 * contain `.cub` suffix. We extract the file data and copy it to
 * our struct for later parsing.
 * `
 * @param data is a pointer to our struct carrying information/data;
 * 
 * @param fname is the first parameter given by the user;
 * 
 * @return map_handling() only returns `SUCCESS` or `FAILURE` upon
 * execution.
 */
int8_t	map_handling(t_data *data, char *fname)
{
	if (check_suffix(fname, ".cub", 5) == FAILURE
		|| open_file(data, fname) == FAILURE)
		return (FAILURE);
	if (repeated_rgb(data->file) == FAILURE
		|| repeated_inline(data->file) == FAILURE)
		return (FAILURE);
	if (extract(data) == FAILURE)
		return (FAILURE);
	if (copy_map(data) == FAILURE)
		return (FAILURE);
	flood_fill(data, (size_t)data->y_ppos, (size_t)data->x_ppos);
	if (check_if_walled(data) == FAILURE)
	{
		free_array(data->mp_cpy);
		return (err_msg(NULL, CLOSE, FAILURE));
	}
	if (data->broken_map == true)
	{
		free_array(data->mp_cpy);
		return (err_msg(NULL, CLOSE, FAILURE));
	}
	free_array(data->mp_cpy);
	return (SUCCESS);
}
