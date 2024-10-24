/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:16 by kotkobay          #+#    #+#             */
/*   Updated: 2024/10/24 11:15:53 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time_stamp_with_message(t_philosophers *philo, double elapsed,
		char *mes)
{
	int	tmp;

	tmp = (int)elapsed;
	printf("%d %d %s\n", tmp, philo->id, mes);
	return ;
}

void	loop_until_died(t_philosophers *philo)
{
	double			elapsed;
	long			seconds;
	long			useconds;
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		seconds = now.tv_sec - start.tv_sec;
		useconds = now.tv_usec - start.tv_usec;
		elapsed = seconds + useconds / 1000000.0;
		if (elapsed >= philo->time_to_die)
		{
			print_time_stamp_with_message(philo, elapsed, "died");
			break ;
		}
		// else if (elapsed >= philo->time_to_die / 2)
		// {
		// 	//食べる（飢餓状態）
		// }
		// else if ()
		// {
		// 	//食べる (通常)
		// }
		// usleep(100000);
	}
}

void	*thread_function(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	printf("Thread %d started\n", philo->id);
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
	philo->times_must_eat = argument->times_must_eat;
	philo->time_to_die = argument->time_to_die;
	philo->time_to_eat = argument->time_to_eat;
	philo->time_to_sleep = argument->time_to_sleep;
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
		exit_with_message("malloc failed");
	while (i < argument->number_of_philosophers)
	{
		philo = create_philo(argument, i);
		status = pthread_create(&(*threads)[i], NULL, thread_function,
				(void *)philo);
		if (status != 0)
			exit_with_message("pthread_create failed");
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
