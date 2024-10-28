/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:16 by kotkobay          #+#    #+#             */
/*   Updated: 2024/10/24 21:48:49 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_time_stamp_with_message(t_philosophers *philo, char *mes)
{
	t_timeval	timeval;

	if (gettimeofday(&timeval, NULL) == 0)
	{
		printf("%ld %d %s\n", timeval.tv_sec, philo->id, mes);
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
		check_live_or_die(philo);
		take_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	*thread_function(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	printf("philosopher %d born\n", philo->id);
	loop_until_died(philo);
	free(philo);
	pthread_exit(NULL);
}

t_philosophers	*create_philo(t_argument *argument, int i)
{
	t_philosophers	*philo;

	philo = malloc(sizeof(t_philosophers));
	if (!philo)
		exit_with_message("malloc failed");
	philo->id = i;
	philo->number_of_philosophers = argument->number_of_philosophers;
	philo->argument = argument;
	return (philo);
}

void	create_thread(t_argument *argument, pthread_t **threads)
{
	t_philosophers	*philo;
	int				i;
	int				status;

	i = 0;
	*threads = malloc(argument->number_of_philosophers * sizeof(pthread_t));
	if (!(*threads))
		exit_with_message("malloc Eroor");
	while (i < argument->number_of_philosophers)
	{
		philo = create_philo(argument, i);
		status = pthread_create(&(*threads)[i], NULL, thread_function,
				(void *)philo);
		if (status != 0)
			exit_free_with_message("pthread_create failed", threads);
		i++;
	}
}

void	operation_thread(t_argument *argument)
{
	pthread_t	*threads;
	void		*thread_result;
	int			status;
	int			i;

	i = 0;
	create_thread(argument, &threads);
	while (i < argument->number_of_philosophers)
	{
		status = pthread_join(threads[i], &thread_result);
		if (status != 0)
			exit_with_message("pthread_join failed");
		i++;
	}
	free(threads);
}
