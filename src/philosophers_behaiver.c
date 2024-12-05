/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/05 12:17:05 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_live_or_die(t_philosophers *philo)
{
	check_elapsed_time(philo);
	check_eating_limits(philo);
	pthread_mutex_lock(&philo->argument->end_mutex);
	if (philo->argument->stop_simulation == 1)
	{
		if (philo->is_holding_left_fork || philo->is_holding_right_fork)
		{
			pthread_mutex_unlock(&philo->forks->mutex[philo->left_fork]);
			philo->is_holding_left_fork = put_fork;
			pthread_mutex_unlock(&philo->forks->mutex[philo->right_fork]);
			philo->is_holding_right_fork = put_fork;
		}
		pthread_mutex_unlock(&philo->argument->end_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philo->argument->end_mutex);
}

void	put_forks(t_philosophers *philo, int put_end)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(&philo->forks->mutex[philo->left_fork]);
		philo->is_holding_left_fork = put_fork;
		pthread_mutex_unlock(&philo->forks->mutex[philo->right_fork]);
		philo->is_holding_right_fork = put_fork;
	}
	else
	{
		pthread_mutex_unlock(&philo->forks->mutex[philo->right_fork]);
		philo->is_holding_right_fork = put_fork;
		pthread_mutex_unlock(&philo->forks->mutex[philo->left_fork]);
		philo->is_holding_left_fork = put_fork;
	}
	if (!put_end)
		print_time_stamp_with_message(philo, "has put a fork");
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
	while (pthread_mutex_trylock(&philo->forks->mutex[left_fork]) != 0)
	{
		philo->is_holding_left_fork = holding_fork;
		check_live_or_die(philo);
		usleep(500);
	}
	while (pthread_mutex_trylock(&philo->forks->mutex[right_fork]) != 0)
	{
		philo->is_holding_right_fork = holding_fork;
		check_live_or_die(philo);
		usleep(500);
	}
}

void	take_forks(t_philosophers *philo)
{
	check_live_or_die(philo);
	if (philo->number_of_philosophers == 1)
	{
		handle_single_philosopher(philo, philo->left_fork);
	}
	else
	{
		lock_forks(philo, philo->left_fork, philo->right_fork);
	}
	check_live_or_die(philo);
	print_time_stamp_with_message(philo, "has taken a fork");
	eat(philo);
	check_live_or_die(philo);
	put_forks(philo, 0);
}
