/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:41:40 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 20:44:21 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_bits(t_philos *philo)
{
	print_action(philo, 0);
	print_action(philo, 0);
	print_action(philo, 1);
	pthread_mutex_lock(&data()->eaten);
	philo->last_eat = (gettime() - data()->start);
	philo->n_eaten++;
	pthread_mutex_unlock(&data()->eaten);
	usleep(data()->time_eat * 1000);
}
