/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/03 20:19:36 by kotkobay         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	// 両方の文字列が NULL の場合は 0 を返す（同じ）
	if (s1 == NULL && s2 == NULL)
		return (0);
	// 文字列が異なる場合、またはどちらかが NULL の場合に処理
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	// 片方の文字列が終わった場合、長さが異なるならその差を返す
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
