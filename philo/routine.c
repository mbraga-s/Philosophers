/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:11:07 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 12:29:58 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Eating action for a philosopher.
//Picks up forks (locks), eats (waits), then puts them down (unlocks).
void	eat(t_philos *philo)
{
	int	i;
	int	j;

	i = philo->id - 1;
	j = i + 1;
	pthread_mutex_lock(&data()->forks[i]);
	if (philo->id == data()->num_philos)
		j = 0;
	pthread_mutex_lock(&data()->forks[j]);
	print_action(philo, 0);
	print_action(philo, 0);
	print_action(philo, 1);
	pthread_mutex_lock(&data()->eaten);
	philo->last_eat = (gettime() - data()->start);
	philo->n_eaten++;
	pthread_mutex_unlock(&data()->eaten);
	usleep(data()->time_eat * 1000);
	pthread_mutex_unlock(&data()->forks[i]);
	pthread_mutex_unlock(&data()->forks[j]);
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

//Checks whether philosophers are dead or have all eaten
//num_has_eat times.
void	wellness_check(void)
{
	int		i;
	time_t	current;

	while (data()->dead != 0 && !data()->flag)
	{
		i = 0;
		while (i < data()->num_philos)
		{
			current = gettime() - data()->start;
			pthread_mutex_lock(&data()->eaten);
			if (current >= ((data()->philos)[i].last_eat + data()->time_die))
			{
				pthread_mutex_unlock(&data()->eaten);
				pthread_mutex_lock(&data()->death);
				data()->dead = 1;
				printf("%ld	%d died.\n",
					(gettime() - data()->start), (data()->philos)[i].id);
				pthread_mutex_unlock(&data()->death);
			}
			else
				pthread_mutex_unlock(&data()->eaten);
			i++;
		}
	}
}

//Runs the philosophers routine until someone dies
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
		usleep(1000 * data()->num_philos);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&data()->death);
		if (data()->dead != 0)
		{
			pthread_mutex_unlock(&data()->death);
			return (NULL);
		}
		pthread_mutex_unlock(&data()->death);
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
