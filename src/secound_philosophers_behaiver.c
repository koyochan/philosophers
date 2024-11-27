/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_philosophers_behaiver.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:20:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/27 11:18:57 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thinking(t_philosophers *philo)
{
	print_time_stamp_with_message(philo, "is thinking");
}

// void	check_elapsed_time(t_philosophers *philo)
// {
// 	long	elapsed_ms;

// 	if (gettimeofday(&philo->now, NULL) != 0)
// 		exit_with_message("Error: gettimeofday failed");
// 	elapsed_ms = (philo->now.tv_sec - philo->start.tv_sec) * 1000;
// 	elapsed_ms += (philo->now.tv_usec - philo->start.tv_usec) / 1000;
// 	if (elapsed_ms >= philo->argument->time_to_die)
// 		handle_death(philo);
// }

// void	handle_death(t_philosophers *philo)
// {
// 	pthread_mutex_lock(&philo->argument->end_mutex);
// 	if (philo->argument->stop_simulation == 0)
// 	{
// 		philo->argument->stop_simulation = 1;
// 		print_time_stamp_with_message(philo, "died");
// 	}
// 	pthread_mutex_unlock(&philo->argument->end_mutex);
// 	if (philo->is_holding_forks)
// 		put_forks(philo, 1);
// 	pthread_exit(NULL);
// }

// void	check_eating_limits(t_philosophers *philo)
// {
// 	if (philo->argument->times_must_eat != -1
// 		&& philo->total_eat_count >= philo->argument->times_must_eat)
// 	{
// 		pthread_mutex_lock(&philo->argument->end_mutex);
// 		if (philo->argument->stop_simulation == 0)
// 			philo->argument->stop_simulation = 1;
// 		pthread_mutex_unlock(&philo->argument->end_mutex);
// 	}
// }