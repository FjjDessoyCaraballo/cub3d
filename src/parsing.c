/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:45:25 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/07 10:39:59 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

static int8_t	is_dir(char **argv)
{
	int	fd;

	fd = open(argv[1], __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	check_name(char **argv)
{
	char	*str;

	if (!ft_strrchr(argv[1], '.'))
		return (FAILURE);
	str = ft_strrchr(argv[1], '.');
	if (ft_strncmp(str, ".cub", 5))
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	open_map(t_data *data, char **argv)
{
	int	fd;

	is_dir(argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	(void)data;
	close(fd);
	return (SUCCESS);	
}

int8_t	map_handling(t_data *data, char **argv)
{
	if (check_name(argv) == FAILURE)
	{
		free(data);
		exit(err_msg(NULL, NAME, 3));
	}
	if (open_map(data, argv) == FAILURE)
	{
		free(data);
		exit(err_msg(NULL, MAP, 4));
	}
	return (SUCCESS);
}