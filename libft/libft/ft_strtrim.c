/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:58:42 by fdessoy-          #+#    #+#             */
/*   Updated: 2023/11/06 11:15:21 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	str = 0;
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= j)
		i++;
	if (i > j)
		return (ft_strdup(s1 + j + 1));
	while (ft_strchr(set, s1[j]) && j >= 0)
		j--;
	str = malloc(j - i + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[i], j - i + 2);
	return (str);
}
