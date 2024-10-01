/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:34:16 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:10:29 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		count;
	int		check;
	va_list	args;

	check = 0;
	count = 0;
	va_start(args, format);
	count = format_check(format, args, &check);
	if (check == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (count);
}
