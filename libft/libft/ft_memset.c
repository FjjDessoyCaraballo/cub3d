/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:13:02 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/10/31 09:49:58 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	value;

	value = (unsigned char)c;
	p = s;
	while (len > 0)
	{
		*p = value;
		p++;
		len--;
	}
	return (s);
}
