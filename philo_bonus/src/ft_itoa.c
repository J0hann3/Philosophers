/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:51:30 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/28 17:55:56 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*write_nb(char *res, int n)
{
	unsigned int	nb;
	int				i;

	nb = n;
	i = 0;
	if (n < 0)
	{
		nb = 0 - n;
		res[i] = '-';
		res[++i] = 0;
	}
	if (nb < 10)
	{
		while (res[i])
			i++;
		res[i] = nb + '0';
		res[++i] = 0;
	}
	else
	{
		write_nb(res, nb / 10);
		write_nb(res, nb % 10);
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	nb;
	char			*res;

	len = 0;
	nb = n;
	if (n < 0)
	{
		len++;
		nb = -n;
	}
	while (nb >= 10)
	{
		len++;
		nb = nb / 10;
	}
	++len;
	res = malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	res[0] = 0;
	res = write_nb(res, n);
	return (res);
}
