/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:14:33 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/13 14:20:09 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_print(char **str)
{
	str[0] = ft_strdup("has taken a fork");
	str[1] = ft_strdup("is eating");
	str[2] = ft_strdup("is sleeping");
	str[3] = ft_strdup("is thinking");
	str[4] = ft_strdup("died");
}
