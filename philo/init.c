/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:19:09 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 12:01:21 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Initializes the data structure.
void	init_data(int argc, char **argv)
{
	data()->num_philos = ft_atoi(argv[1]);
	data()->time_die = ft_atoi(argv[2]);
	data()->time_eat = ft_atoi(argv[3]);
	data()->time_sleep = ft_atoi(argv[4]);
	data()->dead = 0;
	data()->flag = 0;
	if (argc == 6)
		data()->num_has_eat = ft_atoi(argv[5]);
	else
		data()->num_has_eat = 0;
	data()->start = gettime();
	pthread_mutex_init(&data()->writing, NULL);
	pthread_mutex_init(&data()->death, NULL);
	pthread_mutex_init(&data()->eaten, NULL);
}

//Allocates (and initializes) the philosophers and the forks.
//Returns 1 on success and 0 on error.
int	init_philos(void)
{
	int	i;

	i = 0;
	data()->philos = malloc(data()->num_philos * sizeof(t_philos));
	if (!data()->philos)
		return (0);
	data()->forks = malloc(data()->num_philos * sizeof(pthread_mutex_t));
	if (!data()->philos)
		return (0);
	while (i < data()->num_philos)
	{
		data()->philos[i].id = i + 1;
		data()->philos[i].last_eat = 0;
		data()->philos[i].n_eaten = 0;
		pthread_mutex_init(&data()->forks[i], NULL);
		i++;
	}
	return (1);
}
