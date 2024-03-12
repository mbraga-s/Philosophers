/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:11:07 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/12 19:46:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philos *philo)
{
	int	i;
	int	j;

	i = philo->id - 1;
	j = i + 1;
	pthread_mutex_lock(&data()->forks[i]);
	print_action(philo, 0);
	if (philo->id == data()->num_philos)
		j = 0;
	pthread_mutex_lock(&data()->forks[j]);
	print_action(philo, 0);
	print_action(philo, 1);
	philo->last_eat = gettime();
	usleep(data()->time_eat * 1000);
	philo->n_eaten++;
	pthread_mutex_unlock(&data()->forks[i]);
	pthread_mutex_unlock(&data()->forks[j]);
}

void	sleeping(t_philos *philo)
{
	print_action(philo, 2);
	usleep(data()->time_sleep * 1000);
}

void	think(t_philos *philo)
{
	print_action(philo, 3);
}

void	*routine(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (data()->num_philos == 1)
	{
		usleep(data()->time_die * 1000);
		print_action(philo, 4);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(1000);
	eat(philo);
	sleeping(philo);
	think(philo);
	return (NULL);
}
