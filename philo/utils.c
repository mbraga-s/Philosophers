/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/11 16:59:53 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
