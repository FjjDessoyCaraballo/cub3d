/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:13 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/07 14:09:41 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (err_msg(NULL, MALLOC, -1));
		map_handling(data, argv[1]);
		printer(data->file);
		free_array(data->file);
		free(data);
	}
	else
		usage();
	printf("executed to the end\n");
	return (0);
}
