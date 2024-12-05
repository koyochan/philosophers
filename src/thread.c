/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:16 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/05 12:00:10 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_time_stamp_with_message(t_philosophers *philo, char *mes)
{
	t_timeval	timeval;
	long		current_time_in_ms;
	long		elapsed_time;

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

t_philosophers	*create_philo(t_argument *argument, int i, t_forks *forks,
		long start_time_in_ms)
{
	t_philosophers	*philo;

	philo = malloc(sizeof(t_philosophers));
	if (!philo)
		exit_with_message("malloc failed");
	philo->start_time_in_ms = start_time_in_ms;
	philo->forks = forks;
	philo->left_fork = i - 1;
	philo->right_fork = i % argument->number_of_philosophers;
	philo->id = i;
	philo->number_of_philosophers = argument->number_of_philosophers;
	philo->argument = argument;
	return (philo);
}

void	create_thread(t_argument *argument, pthread_t **threads, t_forks *forks,
		long start_time_in_ms)
{
	t_philosophers	*philo;
	int				i;
	int				status;

	i = 1;
	*threads = malloc(argument->number_of_philosophers * sizeof(pthread_t));
	if (!(*threads))
		exit_with_message("malloc Eroor");
	while (i <= argument->number_of_philosophers)
	{
		philo = create_philo(argument, i, forks, start_time_in_ms);
		status = pthread_create(&(*threads)[i], NULL, thread_function,
				(void *)philo);
		if (status != 0)
			exit_with_message("pthread_create failed");
		i++;
	}
}
