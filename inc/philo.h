/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:34:25 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/24 14:40:36 by kotkobay         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_argument
{
	int stop_simulation;
	int total_eat_count;

pthread_mutex_t		end_mutex;
pthread_mutex_t		eat_mutex;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
}						t_argument;

typedef struct s_forks
{
	int					number_of_forks;
	pthread_mutex_t		*mutex;
}						t_forks;

typedef struct s_philosophers
{
	long				start_time_in_ms;
	int					id;
	struct timeval		start;
	struct timeval		now;
	int					how_many_eat;
	int					number_of_philosophers;
	t_argument			*argument;
	t_forks				*forks;
	pthread_t			*threads;
}						t_philosophers;

void					print_time_stamp_with_message(t_philosophers *philo,
							char *mes);
void					check_live_or_die(t_philosophers *philo);
double					ft_atod(const char *str);
void					exit_with_message(char *msg);
void					operation_thread(t_argument *argument, t_forks *forks,
							long start_time_in_ms);
void					take_forks(t_philosophers *philo);
void					sleeping(t_philosophers *philo);
void					thinking(t_philosophers *philo);
void					exit_free_with_message(t_philosophers *philo,
							void *ptr);
t_forks					*init_forks(int number_of_forks);
void					print_forks(t_forks *forks);

#endif