/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:50:01 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/08/29 13:50:03 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_countwords(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (count);
}

static void	*free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	array[count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			array[i] = ft_substr(s, 0, ft_wordlen(s, c));
			if (!array[i++])
				return (free_arr(array));
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (array);
}
