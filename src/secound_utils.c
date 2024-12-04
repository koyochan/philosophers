/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/04 12:21:06 by kotkobay         ###   ########.fr       */
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
	int			status;
	int			i;
	pthread_t	*waiter_thread;
	void		*thread_result;

	// スレッド作成
	create_thread(argument, &threads, &waiter_thread, forks, start_time_in_ms);
	for (i = 0; i < argument->number_of_philosophers; i++) // 修正: <= を < に変更
	{
		if (threads[i] != 0) // 無効なスレッドIDはスキップ
		{
			status = pthread_join(threads[i], &thread_result);
			if (status != 0)
			{
				fprintf(stderr, "pthread_join failed for thread %d\n", i + 1);
				free(threads);
				free(waiter_thread);
				exit_with_message("pthread_join failed");
			}
		}
	}
	if (waiter_thread && *waiter_thread != 0) // 無効なスレッドIDをチェック
	{
		status = pthread_join(*waiter_thread, &thread_result);
		if (status != 0)
		{
			fprintf(stderr, "pthread_join failed for waiter_thread\n");
			free(threads);
			free(waiter_thread);
			exit_with_message("pthread_join failed for waiter_thread");
		}
	}
	// メモリの解放とリソースのクリーンアップ
	free(threads);
	free(waiter_thread);
	cleanup_resources(argument, forks);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
