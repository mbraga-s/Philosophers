/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/11 18:45:15 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Checks for any other character besides digits
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

//Multiply tv_sec by 10^3 and tv_usec (microsec) by 10^-3 to convert to milisec
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
