/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/30 21:10:23 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_live_or_die(t_philosophers *philo)
{
	int	left_fork;
	int	right_fork;

	check_elapsed_time(philo);
	check_eating_limits(philo);
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 1)
	{
		if (philo->is_holding_forks)
		{
			left_fork = philo->id - 1;
			right_fork = philo->id % philo->number_of_philosophers;
			pthread_mutex_unlock(&philo->forks->mutex[left_fork]);
			pthread_mutex_unlock(&philo->forks->mutex[right_fork]);
			philo->is_holding_forks = 0;
		}
		pthread_mutex_unlock(&philo->argument->end_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philo->argument->end_mutex);
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
	int left_fork;
	int right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->number_of_philosophers;

	check_live_or_die(philo);
	if (philo->number_of_philosophers == 1)
	{
		handle_single_philosopher(philo, left_fork);
	}
	else
	{
		lock_forks(philo, left_fork, right_fork);
	}
	philo->is_holding_forks = 1;
	check_live_or_die(philo);
	print_time_stamp_with_message(philo, "has taken a fork");
	eat(philo);
	check_live_or_die(philo);
	put_forks(philo, 0);
}