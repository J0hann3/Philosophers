/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:47:20 by jvigny            #+#    #+#             */
/*   Updated: 2023/03/06 19:33:33 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	res = malloc(sizeof(char) * len + 1);
	if (res == 0)
		return (0);
	while (s1[j])
	{
		res[j] = s1[j];
		j++;
	}
	len = 0;
	while (s2[len])
	{
		res[j] = s2[len];
		j++;
		len++;
	}
	res[j] = 0;
	return (res);
}
