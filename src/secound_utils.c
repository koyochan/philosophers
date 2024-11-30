/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/30 21:32:09 by kotkobay         ###   ########.fr       */
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

	for (i = 0; i < forks->number_of_forks; i++)
		pthread_mutex_destroy(&forks->mutex[i]);
	free(forks->mutex);
	free(forks);
	pthread_mutex_destroy(&argument->end_mutex);
	free(argument);
}

void	operation_thread(t_argument *argument, t_forks *forks,
		long start_time_in_ms)
{
	pthread_t	*threads;
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
	free(threads);
	cleanup_resources(argument, forks);
}
