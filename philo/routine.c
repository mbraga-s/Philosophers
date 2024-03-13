/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:11:07 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 20:49:26 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Eating action for a philosopher.
//Picks up forks (locks), eats (waits), then puts them down (unlocks).
void	eat(t_philos *philo)
{
	if (philo->id == data()->num_philos)
	{
		pthread_mutex_lock(&data()->forks[0]);
		pthread_mutex_lock(&data()->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&data()->forks[philo->id - 1]);
		pthread_mutex_lock(&data()->forks[philo->id]);
	}
	eat_bits(philo);
	if (philo->id == data()->num_philos)
	{
		pthread_mutex_unlock(&data()->forks[philo->id - 1]);
		pthread_mutex_unlock(&data()->forks[0]);
	}
	else
	{
		pthread_mutex_unlock(&data()->forks[philo->id]);
		pthread_mutex_unlock(&data()->forks[philo->id - 1]);
	}
}

//Sleeping action for a philosopher.
//Sleeps for time_to_sleep amount of time (millisec).
void	sleeping(t_philos *philo)
{
	print_action(philo, 2);
	usleep(data()->time_sleep * 1000);
}

//Think action for a philosopher.
//Basically just a printf.
void	think(t_philos *philo)
{
	print_action(philo, 3);
}

//The actual routine
int	routine_loop(t_philos *philo)
{
	pthread_mutex_lock(&data()->death);
	pthread_mutex_lock(&data()->eaten);
	if (data()->dead || data()->flag)
	{
		pthread_mutex_unlock(&data()->death);
		pthread_mutex_unlock(&data()->eaten);
		return (0);
	}
	pthread_mutex_unlock(&data()->death);
	pthread_mutex_unlock(&data()->eaten);
	eat(philo);
	sleeping(philo);
	think(philo);
	return (1);
}

//Runs the philosophers routine until someone dies
void	*routine(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (data()->num_philos == 1)
	{
		lone_philos(philos);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(1000 * data()->num_philos);
	while (1)
	{
		usleep(100);
		if (!routine_loop(philo))
			return (NULL);
	}
	return (NULL);
}
