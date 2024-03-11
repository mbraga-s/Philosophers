/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:28:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/11 18:38:11 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	int		num_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_has_eat;
	time_t	start;
}				t_data;

typedef struct s_philos
{
	pthread_t	thread;
	int			id;
}				t_philos;

long	ft_atoi(const char *nptr);

int		ft_strdigit(char *str);

time_t	gettime(void);

#endif