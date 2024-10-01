/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:28 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:10:20 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointer(void *ptr, int *check)
{
	int	count;

	count = 0;
	count += ft_str("0x", check);
	if (count == -1)
		return (-1);
	count += ft_hex((unsigned long)ptr, 0, check);
	return (count);
}
