/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/17 10:25:01 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_live_or_die(t_philosophers *philo)
{
	long	elapsed_ms;

	if (gettimeofday(&philo->now, NULL) != 0)
	{
		exit_with_message("Error: gettimeofday failed");
	}
	// ミリ秒単位で経過時間を計算
	elapsed_ms = (philo->now.tv_sec - philo->start.tv_sec) * 1000;
	elapsed_ms += (philo->now.tv_usec - philo->start.tv_usec) / 1000;
	// マイクロ秒の計算結果が負の場合の調整
	if (philo->now.tv_usec < philo->start.tv_usec)
	{
		elapsed_ms -= 1000; // 1秒分引く
	}
	// 死亡条件をチェック
	if (elapsed_ms >= philo->argument->time_to_die || *(philo->died) == 1)
	{
		print_time_stamp_with_message(philo, "died");
		pthread_exit(NULL); // スレッド終了
	}
	return ;
}

void	eat(t_philosophers *philo)
{
	struct timeval	start_behaivor;
	int				milliseconds;
	int				useconds;
	double			elapsed;

	elapsed = 0;
	if (gettimeofday(&start_behaivor, NULL) != 0)
	{
		exit_with_message("Error: gettimeofday failed");
	}
	print_time_stamp_with_message(philo, "is eating");
	while (elapsed <= philo->argument->time_to_eat)
	{
		if (gettimeofday(&philo->now, NULL) != 0)
		{
			exit_with_message("Error: gettimeofday failed");
		}
		milliseconds = (philo->now.tv_sec - start_behaivor.tv_sec) * 1000;
		useconds = (philo->now.tv_usec - start_behaivor.tv_usec) / 1000;
		elapsed = milliseconds + useconds;
		usleep(1000);
		check_live_or_die(philo);
	}
	philo->how_many_eat++;
	// if (philo->argument->times_must_eat != -1
	// 	&& philo->how_many_eat >= philo->argument->times_must_eat)
	// {
	// 	// TODO exit all thread and free all memory
	// }
	return ;
}

void	put_forks(t_philosophers *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->number_of_philosophers;
	// 小さい方のフォークからアンロックすることでデッドロックを回避
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&philo->forks->mutex[left_fork]);
		pthread_mutex_unlock(&philo->forks->mutex[right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks->mutex[right_fork]);
		pthread_mutex_unlock(&philo->forks->mutex[left_fork]);
	}
	print_time_stamp_with_message(philo, "has put a fork");
}

void	take_forks(t_philosophers *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->number_of_philosophers;
	// 現在時刻を取得して、nowを更新
	print_time_stamp_with_message(philo, "is taken a fork");
	// 小さい方のフォークからロックすることでデッドロックを回避
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->forks->mutex[left_fork]);
		pthread_mutex_lock(&philo->forks->mutex[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks->mutex[right_fork]);
		pthread_mutex_lock(&philo->forks->mutex[left_fork]);
	}
	// フォークを取った後の処理
	eat(philo);
	put_forks(philo);
}

void	sleeping(t_philosophers *philo)
{
	struct timeval	start_behaivor;
	int				milliseconds;
	int				useconds;
	double			elapsed;

	elapsed = 0;
	if (gettimeofday(&start_behaivor, NULL) != 0)
	{
		exit_with_message("Error: gettimeofday failed");
	}
	print_time_stamp_with_message(philo, "is sleeping");
	while (elapsed <= philo->argument->time_to_sleep)
	{
		if (gettimeofday(&philo->now, NULL) != 0)
		{
			exit_with_message("Error: gettimeofday failed");
		}
		milliseconds = (philo->now.tv_sec - start_behaivor.tv_sec) * 1000;
		useconds = (philo->now.tv_usec - start_behaivor.tv_usec) / 1000;
		elapsed = milliseconds + useconds;
		usleep(1000);
		check_live_or_die(philo);
	}
}
void	thinking(t_philosophers *philo)
{
	print_time_stamp_with_message(philo, "is thinking");
}

void	died(t_philosophers *philo)
{
	pthread_mutex_lock(philo->died_mutex);
	*(philo->died) = 1;
	pthread_mutex_unlock(philo->died_mutex);
}