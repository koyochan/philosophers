/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_behaiver.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:52:55 by kotkobay          #+#    #+#             */
/*   Updated: 2024/10/24 21:51:02 by kotkobay         ###   ########.fr       */
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
	// if (gettimeofday(&philo->start, NULL) != 0)
	// {
	// 	exit_with_message("Error: gettimeofday failed");
	// }
	return ;
}
// void	put_forks(t_philosophers *philo)
// {
// 	return ;
// }
void	take_forks(t_philosophers *philo)
{
	eat(philo);
	// put_forks(philo);
	return ;
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