/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:45:25 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/01 15:22:33 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int8_t	map_handling(t_data *data, char **argv)
{
	if (!check_name(argv))
		exit(err_msg(NULL, NAME, 3));
	if (!open_map(data, argv))
		exit(err_msg(NULL, MAP, 4));
	return (0);
}

int8_t	check_name(char **argv)
{
	(void)argv;
	return (0);
}

int8_t	open_map(t_data *data, char **argv)
{
	(void)argv;
	(void)data;
	return (0);	
}