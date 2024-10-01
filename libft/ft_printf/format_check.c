/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:06:16 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/23 15:09:41 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_id(const char *format, va_list args, int *check)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_char(va_arg(args, int), check);
	else if (*format == 's')
		count += ft_str(va_arg(args, char *), check);
	else if (*format == 'd' || *format == 'i')
		count += ft_nbr(va_arg(args, int), check);
	else if (*format == '%')
		count += ft_char('%', check);
	else if (*format == 'X')
		count += ft_hex(va_arg(args, unsigned int), 1, check);
	else if (*format == 'x')
		count += ft_hex(va_arg(args, unsigned int), 0, check);
	else if (*format == 'u')
		count += ft_unsig_nbr(va_arg(args, unsigned int), check);
	else if (*format == 'p')
		count += ft_pointer(va_arg(args, void *), check);
	if (*check == -1)
		return (-1);
	return (count);
}

int	format_check(const char *format, va_list args, int *check)
{
	int	count;

	count = 0;
	while (*format != '\0')
	{
		if (*format != '%')
		{
			count += ft_char(*format, check);
			if (*check == -1)
				return (-1);
		}
		else if (*format == '%')
		{
			format++;
			count += format_id(format, args, check);
			if (*check == -1)
				return (-1);
		}
		format++;
	}
	return (count);
}
