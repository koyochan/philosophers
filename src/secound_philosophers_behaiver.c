/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_philosophers_behaiver.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:20:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/04 13:31:36 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thinking(t_philosophers *philo)
{
	print_time_stamp_with_message(philo, "is thinking");
}

void	check_elapsed_time(t_philosophers *philo)
{
	long	elapsed_ms;

	if (gettimeofday(&philo->now, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
	elapsed_ms = (philo->now.tv_sec - philo->start.tv_sec) * 1000;
	elapsed_ms += (philo->now.tv_usec - philo->start.tv_usec) / 1000;
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 0
		&& elapsed_ms >= philo->argument->time_to_die)
	{
		pthread_mutex_unlock(&philo->argument->end_mutex); // ロックを先に解放
		handle_death(philo);
		// handle_death 内で再ロック
		return ;
	}
	pthread_mutex_unlock(&philo->argument->end_mutex);
}

void	handle_death(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 0)
	{
		philo->argument->stop_simulation = 1;
		pthread_mutex_unlock(&philo->argument->end_mutex);
		print_time_stamp_with_message(philo, "died");
	}
	else
	{
		pthread_mutex_unlock(&philo->argument->end_mutex);
	}
	if (philo->is_holding_left_fork || philo->is_holding_right_fork)
		put_forks(philo, 1);
	pthread_exit(NULL);
}

void	check_eating_limits(t_philosophers *philo)
{
	if (philo->argument->times_must_eat != -1
		&& philo->total_eat_count >= philo->argument->times_must_eat)
	{
		pthread_mutex_lock(&philo->argument->end_mutex);
		if (philo->argument->stop_simulation == 0)
		{
			philo->argument->stop_simulation = 1;
			pthread_mutex_unlock(&philo->argument->end_mutex);
			pthread_exit(NULL); // スレッド終了
		}
		pthread_mutex_unlock(&philo->argument->end_mutex);
	}
}

void	sleeping(t_philosophers *philo)
{
	struct timeval start_behavior;
	int milliseconds;
	int useconds;
	double elapsed;

	elapsed = 0;
	if (gettimeofday(&start_behavior, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
	check_live_or_die(philo); // 初期チェック
	print_time_stamp_with_message(philo, "is sleeping");
	while (elapsed <= philo->argument->time_to_sleep)
	{
		pthread_mutex_lock(&philo->argument->end_mutex);
		if (philo->argument->stop_simulation)
		{
			pthread_mutex_unlock(&philo->argument->end_mutex);
			break ; // 早期終了
		}
		pthread_mutex_unlock(&philo->argument->end_mutex);

		if (gettimeofday(&philo->now, NULL) != 0)
			exit_with_message("Error: gettimeofday failed");
		milliseconds = (philo->now.tv_sec - start_behavior.tv_sec) * 1000;
		useconds = (philo->now.tv_usec - start_behavior.tv_usec) / 1000;
		elapsed = milliseconds + useconds;
		usleep(100);
		check_live_or_die(philo); // 定期的なチェック
	}
}