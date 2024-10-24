/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:34:25 by kotkobay          #+#    #+#             */
/*   Updated: 2024/05/14 22:15:40 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_timeval
{
	long			tv_sec;
	long			tv_usec;
}					t_timeval;

typedef struct s_argument
{
	int				number_of_philosophers;
	double			time_to_die;
	double			time_to_eat;
	double			time_to_sleep;
	int				times_must_eat;
	int				id;
}					t_argument;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	mutex;
}					t_forks;

typedef struct s_philosophers
{
	int				id;
	int				death;
	int				left_hand;
	int				right_hand;
	int				how_many_eat;
	int				number_of_philosophers;
	double			time_to_die;
	double			time_to_eat;
	double			time_to_sleep;
	int				times_must_eat;
	t_forks			*forks;
	pthread_t		*threads;
}					t_philosophers;

double				ft_atod(const char *str);
void				exit_with_message(char *msg);
void				operation_thread(t_argument *argument);

#endif