/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:11:07 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:11:09 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbr(int n, int *check)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		count += write(1, "-2147483648", 11);
	else if (n < 0)
	{
		count += ft_char('-', check);
		count += ft_nbr(-n, check);
	}
	else if (n >= 10)
	{
		count += ft_nbr(n / 10, check);
		count += ft_char(n % 10 + '0', check);
	}
	else
		count += ft_char(n % 10 + '0', check);
	return (count);
}
