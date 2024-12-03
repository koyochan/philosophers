/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/03 18:13:28 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	exit_with_message(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	cleanup_resources(t_argument *argument, t_forks *forks)
{
	int	i;

	i = 0;
	while (i < forks->number_of_forks)
	{
		pthread_mutex_destroy(&forks->mutex[i]);
		i++;
	}
	free(forks->mutex);
	free(forks);
	pthread_mutex_destroy(&argument->end_mutex);
	free(argument);
}

void	operation_thread(t_argument *argument, t_forks *forks,
		long start_time_in_ms)
{
	pthread_t	*threads;
	pthread_t	*waiter_thread;
	void		*thread_result;
	int			status;
	int			i;

	create_thread(argument, &threads, forks, start_time_in_ms);
	i = 1;
	while (i <= argument->number_of_philosophers)
	{
		status = pthread_join(threads[i], &thread_result);
		if (status != 0)
			exit_with_message("pthread_join failed");
		i++;
	}
	cleanup_resources(argument, forks);
}
