/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:10 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/22 10:52:41 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	a;

	a = count * size;
	if (a < count && a < size)
		return (NULL);
	ptr = malloc(a);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_memset(ptr, 0, a);
	return (ptr);
}
