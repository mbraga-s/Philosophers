/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:06:50 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 16:49:55 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Flips the dead flag when a philosopher dies and prints appropriate msg.
void	philo_byebye(int i)
{
	if (data()->dead || data()->flag)
		return ;
	pthread_mutex_lock(&data()->death);
	data()->dead = 1;
	printf("\e[0;30m%ld	\e[1;32m%d \e[0mdied\n",
		(gettime() - data()->start), (data()->philos)[i].id);
	pthread_mutex_unlock(&data()->death);
}

//Checks if all philosophers have eaten at least the
//given amount of times.
void	philo_yumyum(void)
{
	int	i;

	i = 0;
	while (i < data()->num_philos)
	{
		pthread_mutex_lock(&data()->eaten);
		if ((data()->philos)[i].n_eaten < data()->num_has_eat)
		{
			pthread_mutex_unlock(&data()->eaten);
			return ;
		}
		pthread_mutex_unlock(&data()->eaten);
		i++;
	}
	pthread_mutex_lock(&data()->eaten);
	data()->flag = 1;
	pthread_mutex_unlock(&data()->eaten);
}

//Checks whether philosophers are dead or have all eaten
//num_has_eat times.
void	wellness_check(void)
{
	int		i;
	time_t	current;

	while (!data()->dead && !data()->flag)
	{
		i = 0;
		while (i < data()->num_philos)
		{
			current = gettime() - data()->start;
			pthread_mutex_lock(&data()->eaten);
			if (current >= ((data()->philos)[i].last_eat + data()->time_die))
			{
				pthread_mutex_unlock(&data()->eaten);
				philo_byebye(i);
				break ;
			}
			else
				pthread_mutex_unlock(&data()->eaten);
			i++;
		}
		if (data()->num_has_eat)
			philo_yumyum();
	}
}

//Creates a thread for each philosopher (executing the routine function).
//Checks if any philosopher dies and then joins all the threads.
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
