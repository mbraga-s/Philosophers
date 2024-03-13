/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:28:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/13 12:01:13 by mbraga-s         ###   ########.fr       */
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

typedef struct s_philos
{
	pthread_t	thread;
	int			id;
	int			n_eaten;
	int			last_eat;
}				t_philos;

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_has_eat;
	int				dead;
	int				flag;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	death;
	pthread_mutex_t	eaten;
	time_t			start;
}				t_data;

//main.c

t_data	*data(void);

//init.c

void	init_data(int argc, char **argv);

int		init_philos(void);

//routine.c

void	*routine(void *philos);

void	wellness_check(void);

//threads.c

void	threading(void);

//utils.c

long	ft_atoi(const char *nptr);

int		ft_strdigit(char *str);

time_t	gettime(void);

void	print_action(t_philos *philo, int code);

#endif