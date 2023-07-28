/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:49:18 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/28 15:10:09 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


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
