/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 18:00:21 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Checks for any other character besides digits.
//Returns 1 if any other character is found and 0 if only digits.
int	ft_strdigit(char *str)
{
	if (!str)
		return (1);
	while (str && *str)
	{
		if (*str > '9' || *str < '0')
			return (1);
		str++;
	}
	return (0);
}

//Converts char string to int.
//Returns the int value.
long	ft_atoi(const char *nptr)
{
	size_t		i;
	size_t		sign;
	long		nbr;

	nbr = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45)
	{
		sign = -1;
		i++;
	}
	while ((nptr[i] >= 48 && nptr[i] <= 57))
	{
		nbr = (10 * nbr) + (nptr[i] - 48);
		i++;
	}
	return (nbr * sign);
}

//Returns current time since the EPOCH in miliseconds
//(sec * 10^3 and microsec / 10^3).
time_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (2, "Error retriving time\n", 21);
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//Prints the change of state of given philosopher.
//Code: 0 = fork; 1 = eating; 2 = sleeping; 3 = thinking; 4 = dead.
void	print_action(t_philos *philo, int code)
{
	long	current;

	current = gettime() - data()->start;
	pthread_mutex_lock(&data()->writing);
	if (!data()->dead && !data()->flag)
	{
		printf("\e[1;35m%ld	\e[1;32m%d \e[0m", current, philo->id);
		if (code == 0)
			printf("has taken a fork\n");
		else if (code == 1)
			printf("is eating\n");
		else if (code == 2)
			printf("is sleeping\n");
		else if (code == 3)
			printf("is thinking\n");
		else if (code == 4)
			printf("died\n");
	}
	pthread_mutex_unlock(&data()->writing);
}

//Makes the lone philosopher pick up a fork and then wait to die
void	lone_philos(t_philos *philo)
{
	int	i;

	i = philo->id - 1;
	pthread_mutex_lock(&data()->forks[i]);
	print_action(philo, 0);
	pthread_mutex_unlock(&data()->forks[i]);
	usleep(data()->time_die * 1000);
	print_action(philo, 4);
}
