/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:49:18 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/13 15:50:57 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_str(char **res)
{
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		free(res[i]);
		i++;
	}
	free(res);
}
