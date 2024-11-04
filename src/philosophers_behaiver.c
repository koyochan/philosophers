/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/05 05:58:08 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_live_or_die(t_philosophers *philo)
{
	int		milliseconds;
	int		useconds;
	double	elapsed;

	if (gettimeofday(&philo->now, NULL) != 0)
	{
		exit_with_message("Error: gettimeofday failed");
	}
	milliseconds = (philo->now.tv_sec - philo->start.tv_sec) * 1000;
	useconds = (philo->now.tv_usec - philo->start.tv_usec) / 1000;
	elapsed = milliseconds + useconds;
	if (elapsed >= philo->argument->time_to_die)
	{
		print_time_stamp_with_message(philo, "died");
		free(philo);
		exit(1);
		pthread_exit(NULL);
	}
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