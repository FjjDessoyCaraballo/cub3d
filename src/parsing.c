/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:45:25 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/07 13:09:34 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	is_dir(char *fname)
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

static int8_t	check_name(char *fname)
{
	char	*str;

	if (!ft_strrchr(fname, '.'))
		return (FAILURE);
	str = ft_strrchr(fname, '.');
	if (ft_strncmp(str, ".cub", 5))
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	count_lines(int fd)
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
		return (FAILURE);
	data->file_len = count_lines(open(fname, O_RDONLY));
	if (data->file_len == -1)
		return (FAILURE);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	data->file = ft_calloc(sizeof(char *), data->file_len + 1);
	if (!data->file)
		return (FAILURE);
	i = 0;
	while (i < data->file_len)
		data->file[i++] = get_next_line(fd);
	close(fd);
	return (SUCCESS);	
}

int8_t	map_handling(t_data *data, char *fname)
{
	if (check_name(fname) == FAILURE)
	{
		free(data);
		exit(err_msg(NULL, NAME, 3));
	}
	if (open_file(data, fname) == FAILURE)
	{
		free(data);
		exit(err_msg(NULL, MAP, 4));
	}
	return (SUCCESS);
}