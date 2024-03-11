/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:28:34 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/11 17:03:14 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

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
			|| ft_atoi(argv[i]) < INT_MIN || ft_atoi(argv[i]) < 0)
		{
			write(2, "Invalid arguments\n", 18);
			return (1);
		}
		i++;
	}
	return (0);

}

void	init_data(int argc, char **argv)
{
	data()->num_philos = ft_atoi(argv[1]);
	data()->time_die = ft_atoi(argv[2]);
	data()->time_eat = ft_atoi(argv[3]);
	data()->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data()->num_has_eat = ft_atoi(argv[5]);
	else
		data()->num_has_eat = 0;
}

int	main(int argc, char **argv)
{
	int		i;

	i = 1;
	if (checker(argc, argv))
		return (1);
	init_data(argc, argv);
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}
