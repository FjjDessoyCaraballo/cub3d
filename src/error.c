/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:54:03 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/01 15:19:26 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

int	err_msg(char *obj, char *msg, int exit_code)
{
	if (!obj && msg)
		ft_putstr_fd(msg, 2);
	else if (obj && msg)
	{
		ft_putstr_fd(obj, 2);
		ft_putstr_fd(msg, 2);
	}
	return (exit_code);
}