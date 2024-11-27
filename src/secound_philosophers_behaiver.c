/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_philosophers_behaiver.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:20:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/26 06:42:26 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/philo.h"

// void	dine(t_philosophers *philo)
// {
// 	take_forks(philo);
// 	eat(philo);
// 	put_forks(philo, 0);
// }

// void	sleeping(t_philosophers *philo)
// {
// 	print_time_stamp_with_message(philo, "is sleeping");
// 	wait_time(philo, philo->argument->time_to_sleep);
// }

// void	thinking(t_philosophers *philo)
// {
// 	print_time_stamp_with_message(philo, "is thinking");
// }

// void	take_forks(t_philosophers *philo)
// {
// 	int	left_fork;
// 	int	right_fork;

// 	left_fork = philo->id - 1;
// 	right_fork = philo->id % philo->number_of_philosophers;
// 	if (philo->number_of_philosophers == 1)
// 	{
// 		check_live_or_die(philo);
// 		pthread_mutex_lock(&philo->forks->mutex[left_fork]);
// 		print_time_stamp_with_message(philo, "has taken a fork");
// 		wait_time(philo, philo->argument->time_to_die);
// 		pthread_mutex_unlock(&philo->forks->mutex[left_fork]);
// 		return ;
// 	}
// 	check_live_or_die(philo);
// 	pthread_mutex_lock(&philo->forks->mutex[left_fork]);
// 	pthread_mutex_lock(&philo->forks->mutex[right_fork]);
// 	philo->is_holding_forks = 1;
// 	check_live_or_die(philo);
// 	print_time_stamp_with_message(philo, "has taken a fork");
// }
