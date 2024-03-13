/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:06:50 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 12:11:53 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threading(void)
{
	int	i;

	i = 0;
	while (i < data()->num_philos)
	{
		if (pthread_create(&data()->philos[i].thread, NULL, &routine,
				(void *)&data()->philos[i]))
			return ;
		i++;
	}
	if (data()->num_philos > 1)
		wellness_check();
	i = 0;
	while (i < data()->num_philos)
	{
		if (pthread_join(data()->philos[i].thread, NULL))
			return ;
		i++;
	}
}
