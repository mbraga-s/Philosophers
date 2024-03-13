/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:28:34 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 19:35:39 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Calls the static data structure.
t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

//Destroys all mutexes and frees allocated memory.
void	free_all(void)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data()->writing);
	pthread_mutex_destroy(&data()->death);
	pthread_mutex_destroy(&data()->eaten);
	while (data()->num_philos > i)
	{
		pthread_mutex_destroy(&data()->forks[i]);
		i++;
	}
	free(data()->forks);
	free(data()->philos);
}

//Checks the input provided for letters, values above/below INT MAX and MIN
//and for negative numbers or zero.
//Returns 0 on sucess and 1 if an error is found.
int	checker(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	while (argv[i])
	{
		if (ft_strdigit(argv[i]) || ft_atoi(argv[i]) > INT_MAX
			|| ft_atoi(argv[i]) < INT_MIN || ft_atoi(argv[i]) <= 0)
		{
			write(2, "Invalid arguments\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (checker(argc, argv))
		return (1);
	init_data(argc, argv);
	if (!init_philos())
		return (1);
	threading();
	free_all();
	return (0);
}
