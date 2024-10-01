/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/01 15:20:34 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (err_msg(NULL, MALLOC, -1));
	initializer(data);
	if (argc == 2)
	{
		if (map_handling(data, argv) == 1)
			return (1);
	}
	else
	{
		usage();
		return (1);
	}
	return (0);
}
