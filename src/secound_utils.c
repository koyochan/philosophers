/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/30 20:25:17 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	exit_with_message(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	operation_thread(t_argument *argument, t_forks *forks,
		long start_time_in_ms)
{
	pthread_t	*threads;
	void		*thread_result;
	int			status;
	int			i;

	i = 1;
	create_thread(argument, &threads, forks, start_time_in_ms);
	while (i <= argument->number_of_philosophers)
	{
		status = pthread_join(threads[i], &thread_result);
		if (status != 0)
			exit_with_message("pthread_join failed");
		i++;
	}
	free(threads);
}
