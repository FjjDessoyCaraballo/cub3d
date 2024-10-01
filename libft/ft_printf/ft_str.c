/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:11:26 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:11:29 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str(char *s, int *check)
{
	int	len;

	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	if (write(1, s, len) == -1)
	{
		*check = -1;
		return (-1);
	}
	return (len);
}
