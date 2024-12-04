/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:16 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/04 13:16:27 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_time_stamp_with_message(t_philosophers *philo, char *mes)
{
	t_timeval	timeval;
	long		current_time_in_ms;
	long		elapsed_time;

	if (ft_strcmp(mes, "died") != 0)
	{
		pthread_mutex_lock(&philo->argument->end_mutex);
		if (philo->argument->stop_simulation)
		{
			if (philo->is_holding_left_fork || philo->is_holding_right_fork)
				put_forks(philo, 1);
			pthread_mutex_unlock(&philo->argument->end_mutex);
			pthread_exit(NULL);
		}
		printf("s: %d ", philo->argument->stop_simulation);
		pthread_mutex_unlock(&philo->argument->end_mutex);
	}
	if (gettimeofday(&timeval, NULL) == 0)
	{
		current_time_in_ms = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
		elapsed_time = current_time_in_ms - philo->start_time_in_ms;
		printf("%ld %d %s\n", elapsed_time, philo->id, mes);
	}
	else
	{
		exit_with_message("Error: gettimeofday failed");
	}
	return ;
}

void	loop_until_died(t_philosophers *philo)
{
	if (gettimeofday(&philo->start, NULL) != 0)
	{
		exit_with_message("Error: gettimeofday failed");
	}
	while (1)
	{
		take_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	*thread_function(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	loop_until_died(philo);
	free(philo);
	pthread_exit(NULL);
}

void	*waiter_function(void *arg)
{
	t_argument	*argument;

	argument = (t_argument *)arg;
	while (1)
	{
		pthread_mutex_lock(&argument->end_mutex);
		if (argument->stop_simulation)
		{
			pthread_mutex_unlock(&argument->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&argument->end_mutex);
		usleep(100);
	}
	pthread_exit(NULL);
}

t_philosophers	*create_philo(t_argument *argument, int i, t_forks *forks,
		long start_time_in_ms)
{
	t_philosophers	*philo;

	philo = malloc(sizeof(t_philosophers));
	if (!philo)
		exit_with_message("malloc failed");
	philo->start_time_in_ms = start_time_in_ms;
	philo->forks = forks;
	philo->id = i;
	philo->left_fork = i - 1;
	philo->number_of_philosophers = argument->number_of_philosophers;
	philo->right_fork = i % argument->number_of_philosophers;
	philo->argument = argument;
	return (philo);
}

void	create_thread(t_argument *argument, pthread_t **threads,
		pthread_t **waiter_thread, t_forks *forks, long start_time_in_ms)
{
	t_philosophers	*philo;
	int				i;
	int				status;

	// スレッド配列のメモリ確保
	*threads = malloc(argument->number_of_philosophers * sizeof(pthread_t));
	if (!(*threads))
		exit_with_message("malloc Error");
	// waiter_thread のメモリ確保
	*waiter_thread = malloc(sizeof(pthread_t));
	if (!(*waiter_thread))
	{
		free(*threads); // 既に確保されたメモリを解放
		exit_with_message("malloc Error for waiter_thread");
	}
	// 哲学者スレッドの作成
	for (i = 0; i < argument->number_of_philosophers; i++)
	{
		philo = create_philo(argument, i + 1, forks, start_time_in_ms); // i
		status = pthread_create(&(*threads)[i], NULL, thread_function,
				(void *)philo);
		if (status != 0)
		{
			fprintf(stderr, "pthread_create failed for philosopher %d\n", i
				+ 1);
			free(*threads);
			free(*waiter_thread);
			exit_with_message("pthread_create failed");
		}
	}
	// ウェイタースレッドの作成
	status = pthread_create(*waiter_thread, NULL, waiter_function,
			(void *)argument);
	if (status != 0)
	{
		fprintf(stderr, "pthread_create failed for waiter_thread\n");
		free(*threads);
		free(*waiter_thread);
		exit_with_message("pthread_create for waiter failed");
	}
}
