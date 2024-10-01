/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:01:00 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/01 10:23:18 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			i;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		if (dst == 0 && src == 0 && n > 0)
			return (0);
		cdst[i] = csrc[i];
		i++;
	}
	return (cdst);
}
