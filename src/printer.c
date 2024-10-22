/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:15:00 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/22 11:23:00 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

void	printer(t_data *data)
{
	int i = 0;

	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n");
	i = 0;
	if (data->mp_cpy)
	{
		while (data->mp_cpy[i])
		{
			printf("%s\n", data->mp_cpy[i]);
			i++;
		}
	}
	printf("\n");
	if (data->n_player == true)
	{
		printf("we see this is the player is facing N\n");
		printf("position x: %f\n", data->x_ppos);
		printf("position y: %f\n", data->y_ppos);
	}
	else if (data->s_player == true)
	{
		printf("we see this if the player is facing S\n");
		printf("position x: %f\n", data->x_ppos);
		printf("position y: %f\n", data->y_ppos);
	}
	else if (data->w_player == true)
	{
		printf("we see this if the player is facing W\n");
		printf("position x: %f\n", data->x_ppos);
		printf("position y: %f\n", data->y_ppos);
	}
	else if (data->e_player == true)
	{
		printf("we see this if the player is facing E\n");
		printf("position x: %f\n", data->x_ppos);
		printf("position y: %f\n", data->y_ppos);
	}
	printf("RGB ceiling (red): %u\n", data->c_red);
	printf("RGB ceiling (green): %u\n", data->c_green);
	printf("RGB ceiling (blue): %u\n", data->c_blue);
	printf("RGB floor (red): %u\n", data->f_red);
	printf("RGB floor (green): %u\n", data->f_green);
	printf("RGB floor (blue): %u\n", data->f_blue);
	printf("\nsprites:\n");
	printf("%s", data->n_sprite);
	printf("%s", data->s_sprite);
	printf("%s", data->w_sprite);
	printf("%s", data->e_sprite);
}