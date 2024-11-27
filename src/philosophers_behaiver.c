/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/27 11:18:37 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_elapsed_time(t_philosophers *philo)
{
	long	elapsed_ms;

	if (gettimeofday(&philo->now, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
	elapsed_ms = (philo->now.tv_sec - philo->start.tv_sec) * 1000;
	elapsed_ms += (philo->now.tv_usec - philo->start.tv_usec) / 1000;
	if (elapsed_ms >= philo->argument->time_to_die)
		handle_death(philo);
}

void	handle_death(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 0)
	{
		philo->argument->stop_simulation = 1;
		print_time_stamp_with_message(philo, "died");
	}
	pthread_mutex_unlock(&philo->argument->end_mutex);
	if (philo->is_holding_forks)
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
			philo->argument->stop_simulation = 1;
		pthread_mutex_unlock(&philo->argument->end_mutex);
	}
}

void	check_live_or_die(t_philosophers *philo)
{
	check_elapsed_time(philo);
	check_eating_limits(philo);
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo->argument->end_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philo->argument->end_mutex);
}

void	start_eating_timer(struct timeval *start_behaivor)
{
	if (gettimeofday(start_behaivor, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
}

double	calculate_elapsed_time(struct timeval *start, struct timeval *now)
{
	int	milliseconds;
	int	useconds;

	milliseconds = (now->tv_sec - start->tv_sec) * 1000;
	useconds = (now->tv_usec - start->tv_usec) / 1000;
	return (milliseconds + useconds);
}

void	perform_eating(t_philosophers *philo, struct timeval start_behaivor)
{
	double	elapsed;

	elapsed = 0;
	print_time_stamp_with_message(philo, "is eating");
	while (elapsed <= philo->argument->time_to_eat)
	{
		if (gettimeofday(&philo->now, NULL) != 0)
			exit_with_message("Error: gettimeofday failed");
		elapsed = calculate_elapsed_time(&start_behaivor, &philo->now);
		usleep(500);
		check_live_or_die(philo);
	}
}

void	eat(t_philosophers *philo)
{
	struct timeval	start_behaivor;

	start_eating_timer(&start_behaivor);
	perform_eating(philo, start_behaivor);
	if (gettimeofday(&philo->start, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
	philo->total_eat_count++;
}

void	put_forks(t_philosophers *philo, int put_end)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->number_of_philosophers;
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
	if (!put_end)
		print_time_stamp_with_message(philo, "has put a fork");
	philo->is_holding_forks = 0;
}

void	handle_single_philosopher(t_philosophers *philo, int left_fork)
{
	pthread_mutex_lock(&philo->forks->mutex[left_fork]);
	print_time_stamp_with_message(philo, "has taken a fork");
	usleep(philo->argument->time_to_die * 1000);
	print_time_stamp_with_message(philo, "died");
	pthread_mutex_unlock(&philo->forks->mutex[left_fork]);
	pthread_exit(NULL);
}

void	lock_forks(t_philosophers *philo, int left_fork, int right_fork)
{
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
}

void	take_forks(t_philosophers *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->number_of_philosophers;
	check_live_or_die(philo);
	if (philo->number_of_philosophers == 1)
		handle_single_philosopher(philo, left_fork);
	else
		lock_forks(philo, left_fork, right_fork);
	philo->is_holding_forks = 1;
	check_live_or_die(philo);
	print_time_stamp_with_message(philo, "has taken a fork");
	eat(philo);
	put_forks(philo, 0);
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
		usleep(500);
		check_live_or_die(philo);
	}
}
