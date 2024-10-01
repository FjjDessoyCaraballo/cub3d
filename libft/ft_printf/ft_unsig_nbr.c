/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsig_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:09:07 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:11:38 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsig_nbr(unsigned int n, int *check)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_nbr(n / 10, check);
		count += ft_char(n % 10 + '0', check);
	}
	else
		count += ft_char(n % 10 + '0', check);
	return (count);
}
