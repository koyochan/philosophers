/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:27:37 by kotkobay          #+#    #+#             */
/*   Updated: 2024/12/03 20:03:32 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		usleep(100);
	}
}

void	start_eating_timer(struct timeval *start_behaivor)
{
	if (gettimeofday(start_behaivor, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
}

void	eat(t_philosophers *philo)
{
	struct timeval	start_behaivor;

	start_eating_timer(&start_behaivor);
	if (gettimeofday(&philo->start, NULL) != 0)
		exit_with_message("Error: gettimeofday failed");
	perform_eating(philo, start_behaivor);
	philo->total_eat_count++;
}
