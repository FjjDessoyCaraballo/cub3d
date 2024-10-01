/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:08:53 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/20 16:33:41 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			i;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (dst < src && i < len)
	{
		cdst[i] = csrc[i];
		i++;
	}
	while (dst > src && len > 0)
	{
		cdst[len - 1] = csrc[len - 1];
		len--;
	}
	return ((void *)cdst);
}
